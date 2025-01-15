#include "minishell.h"

char	**ft_get_matrix(char *input)
{
	char	**arg;
	char	**matrix;
	int i;

	i = 0;
	arg = ft_split_quoted(input, ' ');
	while (arg[i])
		i++;
	free(input);
	matrix = ft_copy_matrix(arg, i);
	ft_free_matrix(arg);
	return (matrix);
}

void	ft_write_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	ft_putendl_fd(": command not found", 2);
}

void	ft_check_cmd(char **matrix)
{
	if (ft_strcmp(matrix[0], ("echo")) == 0)
		ft_echo(matrix);
	else if (ft_strcmp(matrix[0], ("cd")) == 0)
		ft_cd(matrix);
	else if (ft_strcmp(matrix[0], ("pwd")) == 0)
		ft_pwd(matrix);
	else if (ft_strcmp(matrix[0], ("export")) == 0)
		ft_export(matrix);
	else if (ft_strcmp(matrix[0], ("unset")) == 0)
		ft_unset(matrix);
	else if (ft_strcmp(matrix[0], ("exit")) == 0)
		ft_exit(matrix);
	else
		ft_write_error(matrix[0]);
}
void ft_read_inputs(char *input)
{
	char **matrix;
	
	if (input == NULL || input[0] == '\0')
	{
		printf("exit\n");
		free(input);
		exit(1);
	}
	if (input[0] != '\0')
		add_history(input);
	ft_expand_var(&input);
	if (ft_check_quote(input) == -1)
		write(2, "Sintax: erro\n", 13);
	else
	{
		matrix = ft_get_matrix(input);
		ft_check_cmd(matrix);
	}
}

int main(int argc, char **argv, char *env[])
{
	char *input;
	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		input = readline("> ");
		ft_read_inputs(input);
		// free(input);
	}
	return (0);
}
