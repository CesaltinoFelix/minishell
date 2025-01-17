#include "../minishell.h"

static int ft_echo_with_n(char **matrix)
{
	int i;
	int j;
	int flag;

	i = 1;
	flag = 1;
	while (matrix[i])
	{
		if (matrix[i][0] == '-' && matrix[i][1] == 'n')
		{
			j = 1;
			while (matrix[i][j] == 'n')
				j++;
			if (matrix[i][j] != '\0')
				break;
			else
			{
				flag = 0;
				break;
			}
		}
		break;
		i++;
	}
	return (flag);
}

int ft_echo(char **matrix)
{
	int i = 1;
	int new_line = 1;

	if (ft_echo_with_n(matrix) == 0)
	{
		new_line = 0;
		// while (matrix[i] && matrix[i][0] == '-' && matrix[i][1] == 'n')
		//     i++;
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

	return (0);
}
