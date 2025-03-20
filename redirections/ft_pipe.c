#include "../minishell.h"

int is_builtin(char *cmd) {
    return (ft_strcmp(cmd, "echo") == 0 || 
            ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}

t_pipeline *split_commands(t_minishell *shell, int *cmd_count) {
    int i = 0;
    int j = 0;
    t_pipeline *cmds = malloc(sizeof(t_pipeline) * 10); // Ajustar alocação
    
    while (shell->parsed_input[i]) {
        cmds[j].cmd_args = &shell->parsed_input[i];
        cmds[j].fd_in = STDIN_FILENO;
        cmds[j].fd_out = STDOUT_FILENO;
        
        while (shell->parsed_input[i] && ft_strcmp(shell->parsed_input[i], "|") != 0)
            i++;
        
        if (shell->parsed_input[i] && ft_strcmp(shell->parsed_input[i], "|") == 0) {
            shell->parsed_input[i] = NULL; // Terminar array atual
            i++;
        }
        cmds[j].is_last = (shell->parsed_input[i] == NULL);
        j++;
    }
    *cmd_count = j;
    return cmds;
}



static char *get_output_file(char **cmd_args)
{
    int i = 0;
    while (cmd_args[i])
    {
        if (ft_strcmp(cmd_args[i], ">") == 0 || ft_strcmp(cmd_args[i], ">>") == 0)
        {
            if (cmd_args[i + 1])
                return (cmd_args[i + 1]);
            else
                return (NULL); // Erro: arquivo não especificado
        }
        i++;
    }
    return (NULL); // Sem redirecionamento
}
// Funções auxiliares para verificar e aplicar redirecionamentos
static char *get_input_file(char **cmd_args)
{
    int i = 0;
    while (cmd_args[i])
    {
        if (ft_strcmp(cmd_args[i], "<") == 0)
        {
            if (cmd_args[i + 1])
                return (cmd_args[i + 1]);
            else
                return (NULL); // Erro: arquivo não especificado
        }
        i++;
    }
    return (NULL); // Sem redirecionamento
}

static void remove_input_redirection_tokens(char **cmd_args)
{
    int i = 0;
    while (cmd_args[i])
    {
        if (ft_strcmp(cmd_args[i], "<") == 0)
        {
            free(cmd_args[i]);
            free(cmd_args[i + 1]);
            while (cmd_args[i + 2])
            {
                cmd_args[i] = cmd_args[i + 2];
                i++;
            }
            cmd_args[i] = NULL;
            cmd_args[i + 1] = NULL;
            break;
        }
        i++;
    }
}

// Função para remover tokens de redirecionamento
static void remove_redirection_tokens(char **cmd_args)
{
    int i = 0;
    while (cmd_args[i])
    {
        if (ft_strcmp(cmd_args[i], ">") == 0 || ft_strcmp(cmd_args[i], ">>") == 0)
        {
            free(cmd_args[i]);
            free(cmd_args[i + 1]);
            while (cmd_args[i + 2])
            {
                cmd_args[i] = cmd_args[i + 2];
                i++;
            }
            cmd_args[i] = NULL;
            cmd_args[i + 1] = NULL;
            break;
        }
        i++;
    }
}
void execute_pipeline(t_minishell *shell, t_pipeline *cmds, int cmd_count)
{
    int pipes[2];
    int prev_pipe_in = 0;
    pid_t pid;

    for (int i = 0; i < cmd_count; i++)
    {
        if (i < cmd_count - 1)
            pipe(pipes);

        pid = fork();
        if (pid == 0)
        {
            // Redirecionar entrada
            if (i > 0)
                dup2(prev_pipe_in, STDIN_FILENO);

            // Verificar e aplicar redirecionamentos de saída
            char *output_file = get_output_file(cmds[i].cmd_args);
            if (output_file)
            {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    exit(1);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                remove_redirection_tokens(cmds[i].cmd_args);
            }

            // Verificar e aplicar redirecionamentos de entrada
            char *input_file = get_input_file(cmds[i].cmd_args);
            if (input_file)
            {
                int fd = open(input_file, O_RDONLY);
                if (fd == -1)
                    exit(1);
                dup2(fd, STDIN_FILENO);
                close(fd);
                remove_input_redirection_tokens(cmds[i].cmd_args);
            }

            // Redirecionar saída para o próximo pipe
            if (i < cmd_count - 1 && !output_file)
                dup2(pipes[1], STDOUT_FILENO);

            // Fechar descritores não usados
            close(pipes[0]);
            if (i < cmd_count - 1)
                close(pipes[1]);

            // Executar comando
            shell->parsed_input = cmds[i].cmd_args;
            if (is_builtin(cmds[i].cmd_args[0]))
                execute_command(shell);
            else
                execute_external_command(shell);
            exit(shell->exit_status);
        }
        else
        {
            if (i > 0)
                close(prev_pipe_in);
            if (i < cmd_count - 1) {
                prev_pipe_in = pipes[0];
                close(pipes[1]);
            }
        }
    }

    // Esperar todos os processos filhos
    while (waitpid(0, &shell->exit_status, 0) > 0);
    shell->exit_status = WEXITSTATUS(shell->exit_status);
}