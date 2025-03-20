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

void execute_pipeline(t_minishell *shell, t_pipeline *cmds, int cmd_count) {
    int pipes[2];
    int prev_pipe_in = 0;
    pid_t pid;

    for (int i = 0; i < cmd_count; i++) {
        if (i < cmd_count - 1)
            pipe(pipes);

        pid = fork();
        if (pid == 0) {
            // Redirecionar entrada
            if (i > 0)
                dup2(prev_pipe_in, STDIN_FILENO);
            
            // Redirecionar saída
            if (i < cmd_count - 1)
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
        } else {
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
