#include "../minishell.h"

char *ft_strndup(const char *s, size_t len)
{
	char *ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, (len + 1));
	return (ptr);
}

int ft_check_quote(char *str)
{
	int i;
	int status;

	i = 0;
	status = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			status = 1;
			while (str[i] && !(str[i] == '"' && str[i - 1] != '\\'))
				i++;
			if (str[i] == '\0')
				return (-1);
		}else
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		{
			i++;
			status = 2;
			while (str[i] && !(str[i] == '\'' && str[i - 1] != '\\'))
				i++;
			if (str[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (status);
}

int ft_strlen_unquote(char *str, int type_quote)
{
	int i;
	int count;
	char c;
	i = 0;
	count = 0;

	if(type_quote == 1)
		c = '"';
	else
		c = '\'';

	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

int ft_strcpy_unquote(char *dest, const char *src, int size,  int type_quote)
{
	int i;
	int j;
	int c;

	i = 0;
	j = 0;
	if(type_quote == 1)
		c = '"';
	else
		c = '\'';
	while (j < size && src[i] != '\0')
	{
		if (src[i] == c)
			i++;
		else
		{
			dest[j] = src[i];
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char **ft_copy_matrix(char **matrix, int size, int type_quote)
{
	char **copy_matrix;
	int j;
	int len;

	j = 0;
	copy_matrix = malloc(sizeof(char *) * (size + 1));
	while (matrix[j] && j < size)
	{
		len = ft_strlen_unquote(matrix[j], type_quote);
		copy_matrix[j] = malloc(sizeof(char) * (len + 1));
		ft_strcpy_unquote(copy_matrix[j], matrix[j], (int)len, type_quote);
		j++;
	}
	copy_matrix[j] = '\0';
	return (copy_matrix);
}
