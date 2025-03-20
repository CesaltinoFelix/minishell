#include "minishell.h"

void ft_run_execve(t_minishell *shell, int *i, char **path)
{
    char *tmp;

    while (shell->system_paths[++(*i)])
    {
        tmp = ft_strjoin(shell->system_paths[*i], "/");
        if (!*tmp)
            continue;
        *path = ft_strjoin(tmp, shell->parsed_input[0]);
        free(tmp);
        if (!*path)
            continue;
        execve(*path, shell->parsed_input, shell->env_variables);
        free(*path);
    }
}

int execute_external_command(t_minishell *shell)
{
    pid_t pid;
    char *path;
    int i;

    i = -1;
    path = NULL;
    pid = fork();
    if (pid == -1)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        path = getenv("PATH");
        shell->system_paths = ft_split(path, ':');
        if (!shell->system_paths)
            exit(1);
        ft_run_execve(shell, &i, &path);
        ft_write_error(shell->parsed_input[0]);
        ft_free_matrix(shell->system_paths);
        exit(127);
    }
    else
        waitpid(pid, &shell->exit_status, 0);
    return (WEXITSTATUS(shell->exit_status));
}

int execute_command(t_minishell *shell)
{
    if (ft_strcmp(shell->parsed_input[0], "echo") == 0)
        return handle_echo_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "cd") == 0)
        return handle_cd_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "pwd") == 0)
        return handle_pwd_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "export") == 0)
        return handle_export_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "unset") == 0)
        return handle_unset_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "env") == 0)
        return handle_env_command(shell);
    else if (ft_strcmp(shell->parsed_input[0], "exit") == 0)
    {
        handle_exit_command(shell);
        return shell->exit_status;
    }
    else
        return execute_external_command(shell);
}

void process_user_input(t_minishell *shell)
{
    int cmd_count;
    t_pipeline *cmds;

    if (get_quote_status(shell->input) == -1)
    {
        shell->exit_status = 2;
        return;
    }

    expand_all_env_variables(shell);
    shell->parsed_input = tokenize_input(shell);

    cmds = split_commands(shell, &cmd_count);

    if (cmd_count > 1)
        execute_pipeline(shell, cmds, cmd_count);
    else
    {
        if (ft_handle_redirections(shell) == -1)
        {
            shell->exit_status = 2;
            return;
        }
        execute_command(shell);
    }

    ft_restore_stdio(shell);
    free(cmds);
}

void run_shell(t_minishell *shell)
{
    char *trimmed_input;

    while (1)
    {
        shell->input = readline("minishell> ");
        if (!shell->input)
        {
            printf("exit\n");
            break;
        }
        trimmed_input = trim_whitespace(shell->input);
        free(shell->input);
        shell->input = trimmed_input;
        if (*shell->input)
        {
            add_history(shell->input);
            process_user_input(shell);
        }
        check_to_free(shell);
    }
    ft_free_matrix(shell->env_variables);
    check_to_free(shell);
}
