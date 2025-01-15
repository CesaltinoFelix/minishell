#include "../minishell.h"

static int ft_echo_with_n(char **matrix)
{
	return (matrix[0] && strcmp(matrix[0], "echo") == 0 
	&& matrix[1] && strcmp(matrix[1], "-n") == 0);
}

void ft_echo(char **matrix)
{
	
	int i;
	int new_line;

	i = 1;
	new_line = 1;
	if (ft_echo_with_n(matrix))
	{
		new_line = 0;
		i = 2;
	}
	while (matrix[i])
	{
		printf("%s", matrix[i]);
		if (matrix[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
}
