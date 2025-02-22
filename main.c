#include "minishell.h"

char **ft_cpy_env(char *env[])
{
    int i;
    char **new_env;

    i = -1;
    while (env[++i]);
    new_env = malloc(sizeof(char *) * (i + 1));
    if (new_env == NULL)
        return (NULL);
    i = -1;
    while (env[++i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (new_env[i] == NULL)
            return (ft_free_matrix(new_env), NULL);
    }
    new_env[i] = NULL;
    return (new_env);
}

void ft_init_env(t_minishell *shell)
{
    shell->env.key_len = 0;
    shell->env.key = NULL;
    shell->env.value = NULL;
    shell->env.new_var = NULL;
    shell->env.equal_sign = NULL;
}

void init_shell(t_minishell *shell, char *env[])
{
    shell->exp.len = 0;
    shell->exp.start = NULL;
    shell->exp.end = NULL;
    shell->exp.var_name = NULL;
    shell->exp.var_value = NULL;
    ft_init_env(shell);
    shell->env_var = ft_cpy_env(env);
    shell->input = NULL;
    shell->matrix = NULL;
    shell->sv_path = NULL;
    shell->old_path = NULL;
    shell->current_path = NULL;
    shell->last_exit_code = 0;
    shell->status = 0;
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->stdin_backup = dup(STDIN_FILENO);

}

char **ft_get_matrix(t_minishell *shell)
{
    char **arg;
    int i;

    i = -1;
    arg = ft_split_quoted(shell->input, ' ');
    if (arg == NULL)
        return (NULL);
    while (arg[++i]);
    shell->matrix = ft_copy_matrix(arg, i);
    ft_free_matrix(arg);
    if (shell->matrix == NULL)
        return (NULL);
    return (shell->matrix);
}

void ft_write_error(char *str)
{
    while (*str)
        write(2, str++, 1);
    ft_putendl_fd(": command not found", 2);
}

int ft_execute_bin(t_minishell *shell)
{
    pid_t pid;
    char *path = NULL;
    int i = -1;
    int exec_ = 0;
    pid = fork();
    if (pid == -1)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        path = getenv("PATH");
        shell->sv_path = ft_split(path, ':');
        while (shell->sv_path[++i])
        {
            ft_strcat(shell->sv_path[i], "/");
            path = ft_strjoin(shell->sv_path[i], shell->matrix[0]);
            if (execve(path, shell->matrix, shell->env_var) != -1)
                exec_ = 1;
        }
        if (!exec_)
        {
            ft_write_error(shell->matrix[0]);
            exit(127);
        }
    }
    else
        waitpid(pid, &shell->status, 0);
    return (WEXITSTATUS(shell->status));
}

int ft_check_cmd(t_minishell *shell)
{
    if (ft_strcmp(shell->matrix[0], "echo") == 0)
    shell->status = ft_echo(shell);
    else if (ft_strcmp(shell->matrix[0], "cd") == 0)
        shell->status = ft_cd(shell);
    else if (ft_strcmp(shell->matrix[0], "pwd") == 0)
        shell->status = ft_pwd(shell);
    else if (ft_strcmp(shell->matrix[0], "export") == 0)
        shell->status = ft_export(shell);
    else if (ft_strcmp(shell->matrix[0], "unset") == 0)
        shell->status = ft_unset(shell);
    else if (ft_strcmp(shell->matrix[0], "env") == 0)
        shell->status = ft_env(shell);
    else if (ft_strcmp(shell->matrix[0], "exit") == 0)
        ft_exit(shell);
    else
        shell->status = ft_execute_bin(shell);
    return (shell->status);
}

int ft_check_escape(char *str, char *pos)
{
    int count_escape;
    
    count_escape = 0;
    while (pos > str && *(pos - 1) == '\\')
    {
        count_escape++;
        pos--;
    }
    return (count_escape);
}

// void ft_replace_in(char **input)
// {
//     int total_chr;
    
//     total_chr = ft_check_escape(*input);
//     if (total_chr % 2 == 0)
//         *input += total_chr / 2;
//     else
//         *input += (total_chr / 2 ) + (total_chr % 2);
// }
void ft_read_inputs(t_minishell *shell)
{
    if (ft_check_quote(shell->input) == -1)
    {
        printf("error: input invalid: %s\n", shell->input);
        return;
    }
    else
    {
        ft_expand_var(&shell->input);
        // ft_replace_in(&shell->input);
        shell->matrix = ft_get_matrix(shell);
        if (ft_handle_redirections(shell) == -1)
        	return;
        if (ft_check_cmd(shell) == 0)
            printf("status %d\n", shell->status);
        else
            printf("status %d\n", shell->status);
        ft_restore_stdio(shell);
    }
}
char *trim_whitespace(char *str)
{
    char *end;

    while (ft_isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return (str);
    end = str + strlen(str) - 1;
    while (end > str && ft_isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return (str);
}

void check_to_free(t_minishell *shell)
{
    if (shell->input)
        free(shell->input);
    if (shell->matrix)
        ft_free_matrix(shell->matrix);
    if (shell->env_var)
        ft_free_matrix(shell->env_var);
}

void run_shell(t_minishell *shell)
{
    while (1)
    {
        shell->input = readline("minishell> ");
        if (shell->input == NULL)
        {
            printf("exit\n");
            break;
        }
        shell->input = trim_whitespace(shell->input);
        if (shell->input[0] != '\0')
        {
            add_history(shell->input);
            ft_read_inputs(shell);
        }
        else
            continue;
    }
    check_to_free(shell);
}

int main(int argc, char const *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    t_minishell shell;

    setup_signal_handlers();
    init_shell(&shell, env);
    run_shell(&shell);
    return 0;
}
