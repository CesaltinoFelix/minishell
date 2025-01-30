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
        }
        else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
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

int ft_strlen_unquote(const char *str)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            char quote = str[i];
            i++;
            while (str[i] && str[i] != quote)
            {
                i++;
                count++;
            }
            if (str[i] == quote)
                i++;
        }
        else
        {
            i++;
            count++;
        }
    }
    return (count);
}

int ft_strcpy_unquote(char *dest, const char *src, int size)
{
    int i = 0;
    int j = 0;

    while (src[i] && j < size)
    {
        if (src[i] == '"' || src[i] == '\'')
        {
            char quote = src[i];
            i++;
            while (src[i] && src[i] != quote && j < size)
            {
                dest[j++] = src[i++];
            }
            if (src[i] == quote)
                i++;
        }
        else
        {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
    return (i);
}

char **ft_copy_matrix(char **matrix, int size)
{
    char **copy_matrix;
    int j, len;

    j = 0;
    copy_matrix = malloc(sizeof(char *) * (size + 1));
    if (!copy_matrix)
        return (NULL);

    while (matrix[j] && j < size)
    {
        len = ft_strlen_unquote(matrix[j]);
        copy_matrix[j] = malloc(sizeof(char) * (len + 1));
        if (!copy_matrix[j])
        {
            while (--j >= 0)
                ft_free_matrix(copy_matrix);
            return (NULL);
        }
        ft_strcpy_unquote(copy_matrix[j], matrix[j], len);
        j++;
    }
    copy_matrix[j] = NULL;
    return (copy_matrix);
}

void ft_sort_string_matrix(char **matrix)
{
    int i;
    int len;
    char *tmp;

    i = 0;
    len = -1;
    tmp = NULL;
    while (matrix[++len])
        ;
    while (i < len - 1)
    {
        if (ft_strcmp(matrix[i], matrix[i + 1]) > 0)
        {
            tmp = matrix[i];
            matrix[i] = matrix[i + 1];
            matrix[i + 1] = tmp;
            i = 0;
        }
        else
            i++;
    }
}