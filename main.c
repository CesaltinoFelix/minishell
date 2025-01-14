#include "minishell.h"

void ft_free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

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

void ft_cmd_error(char *str)
{
	char *start;
	char *end;
	char *ptr;
	start = ft_strchr(str, '"');
	end = ft_strrchr(start + 1, '"');
	if (!start || !end)
		return;
	ptr = start + 1;
	while (ptr < end)
	{
		printf("%c", *ptr);
		ptr++;
	}
	printf(": command not found\n");
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
	else if (ft_check_quote(input) == 1 && input[0] == '"')
	{
		ft_cmd_error(input);
	}
	else
	{
		matrix = ft_get_matrix(input);
		if (ft_strlen(matrix[0]) > ft_strlen("echo"))
			printf("%s: command not found", matrix[0]);
		ft_echo(matrix);
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
		free(input);
	}
	return (0);
}
