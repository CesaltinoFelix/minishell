#include "minishell.h"


void	ft_get_matrix(char *str, char **matrix)
{
	char	**arg;
	int	i;

	i = 0;
	arg = ft_split_quoted(str, ' ');

	while (arg[i])
	{
		printf("token[%d] = %s\n", i, arg[i]);
		i++;
	}
	matrix = ft_copy_matrix(arg, i);
	i = 0;
	printf("\n\n\n");
	while (matrix[i])
	{
		printf("token[%d] = %s\n", i, matrix[i]);
		i++;
	}
}

int	main(int argc, char **argv, char *env[])
{
	char *input;
	(void)argc;
	(void)argv;
	(void)env;
	char **matrix;

	matrix = NULL;
	while (1)
	{
		input  = readline("> ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		if (input[0] != '\0')
			add_history(input);
		ft_expand_variables(&input);
		printf("Before tokens: %s\n", input);
		ft_get_matrix(input, matrix);
		//printf("After tokens: %s\n", input);
	}
	return (0);
}
