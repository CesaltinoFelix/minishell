#include "minishell.h"

char **ft_get_matrix(char *input, int type_quote)
{
	char **arg;
	char **matrix;
	int i;

	i = 0;
	arg = ft_split_quoted(input, ' ');
	while (arg[i])
		i++;
	free(input);
	matrix = ft_copy_matrix(arg, i, type_quote);
	ft_free_matrix(arg);
	return (matrix);
}

int ft_write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	ft_putendl_fd(": command not found", 2);
	return (2);
}

int ft_check_cmd(char **matrix)
{
	int	status;

	status = 0;
	if (ft_strcmp(matrix[0], "echo") == 0)
		status = ft_echo(matrix);
	else if (ft_strcmp(matrix[0], "cd") == 0)
		status = ft_cd(matrix);
	else if (ft_strcmp(matrix[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(matrix[0], "export") == 0)
		status = ft_export(matrix);
	else if (ft_strcmp(matrix[0], "unset") == 0)
		status = ft_unset(matrix);
	else if (ft_strcmp(matrix[0], "env") == 0)
		status = ft_env(matrix);
	else if (ft_strcmp(matrix[0], "exit") == 0)
		status = ft_exit(matrix);
	else
		status = ft_write_error(matrix[0]);
	return (status);
}

void ft_read_inputs(char *input)
{
	char **matrix;
	int type_quote;

	if (input == NULL || input[0] == '\0')
	{
		free(input);
		return;
	}
	if (input[0] != '\0')
		add_history(input);
	ft_expand_var(&input);
	type_quote = ft_check_quote(input);
	if (type_quote == -1)
		write(2, "Sintax: erro\n", 13);
	else
	{
		matrix = ft_get_matrix(input, type_quote);
		ft_check_cmd(matrix);
	}
}

int main(int argc, char **argv)
{
	char *input;
	(void)argc;
	(void)argv;

	while (1)
	{
		input = readline("minishell> ");
		ft_read_inputs(input);
		// free(input);
	}
	return (0);
}
