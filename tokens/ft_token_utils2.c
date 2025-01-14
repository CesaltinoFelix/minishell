#include "../minishell.h"

int ft_strlen_matrix(char **matrix)
{
	int i;
	int j;
	int count;

	i = -1;
	count = 0;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j])
		{
			count++;
			j++;
		}
	}
	if (i > 1)
		count += i - 1;
	return (count);
}

char *ft_cpy_matrix_to_string(char **matrix)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int len = ft_strlen_matrix(matrix);
	char *str = malloc(sizeof(char) * (len + 1));

	while (matrix[i] && j < len)
	{
		k = 0;
		while (matrix[i][k])
		{
			str[j] = matrix[i][k];
			k++;
			j++;
		}
		if (matrix[i + 1])
			str[j++] = ' ';
		i++;
	}
	str[j] = '\0';
	return (str);
}