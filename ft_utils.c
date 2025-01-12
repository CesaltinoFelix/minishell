#include "minishell.h"

char	*ft_strndup(const char *s, size_t	len)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, (len + 1));
	return (ptr);
}

int ft_strlen_quote(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == '"')
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}


int	ft_strcpy_quote(char *dest, const char *src, int size)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (j < size && src[i] != '\0')
	{
		if(src[i] == '"')
			i++;
		else
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char** ft_copy_matrix(char **matrix, int i)
{
	char **copy_matrix;
	int j;
	int len;
	j = 0;
	
	copy_matrix = malloc(sizeof(char *) * (i + 1));
	while (matrix[j]  && j < i)
	{	
		len = ft_strlen_quote(matrix[j]);
		copy_matrix[j] = malloc(sizeof(char) * (len + 1));
		ft_strcpy_quote(copy_matrix[j], matrix[j], (int)len);
		j++;
	}
	
	copy_matrix[j] = '\0';
	return (copy_matrix);
}