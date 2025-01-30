#include "minishell.h"

char **ft_cpy_env(char *env[])
{
    int i;
    char **new_env;

    i = -1;
    while (env[++i])
        ;
    new_env = malloc(sizeof(char *) * (i + 1));
    if (new_env == NULL)
        return (NULL);
    i = -1;
    while (env[++i])
        new_env[i] = ft_strdup(env[i]);
    new_env[i] = NULL;
    return (new_env);
}

void    ft_init_env(t_minishell *shell)
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
        shell->old_path = NULL;
        shell->current_path = NULL;
        shell->last_exit_code = 0;
}

char **ft_get_matrix(t_minishell *shell)
{
	char **arg;
	int i;

	i = -1;
	arg = ft_split_quoted(shell->input, ' ');
	while (arg[++i]);
	shell->matrix = ft_copy_matrix(arg, i);
	free(shell->input);
        ft_free_matrix(arg);
	return (shell->matrix);
}

int ft_write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	ft_putendl_fd(": command not found", 2);
	return (2);
}

int ft_check_cmd(t_minishell *shell)
{
	int	status;
	
	status = 0;
	if (ft_strcmp(shell->matrix[0], "echo") == 0)
		status = ft_echo(shell);
	else if (ft_strcmp(shell->matrix[0], "cd") == 0)
		status = ft_cd(shell);
	else if (ft_strcmp(shell->matrix[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(shell->matrix[0], "export") == 0)
		status = ft_export(shell);
	else if (ft_strcmp(shell->matrix[0], "unset") == 0)
		status = ft_unset(shell);
	else if (ft_strcmp(shell->matrix[0], "env") == 0)
		status = ft_env(shell);
	else if (ft_strcmp(shell->matrix[0], "exit") == 0)
		status = ft_exit(shell);
        else
                status = ft_write_error(shell->matrix[0]);
        return (status);
}

void ft_read_inputs(t_minishell *shell)
{
        if (ft_check_quote(shell->input) == -1)
        {
                printf("error: input invalid: %s\n", shell->input);
                free(shell->input);
                return;
        }
        else
        {
                shell->matrix = ft_get_matrix(shell);
                ft_check_cmd(shell);
        }
}

int main(int argc, char const *argv[], char *env[])
{
        (void)argc;
        (void)argv;
        t_minishell shell;

        init_shell(&shell, env);
        while (1)
        {
                shell.input = readline("minishell> ");
                if (!shell.input || shell.input[0] == '\0')
                {
                        free(shell.input);
                        ft_free_matrix(shell.matrix);
                        return (1);
                }
                if (shell.input[0] != '\0')
                        add_history(shell.input);
                ft_read_inputs(&shell);
        }
        free(shell.input);
        return 0;
}
