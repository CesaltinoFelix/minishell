#include "../minishell.h"

char *ft_strndup(const char *input, size_t len)
{
    char *copy = malloc(len + 1);
    if (!copy)
        return (NULL);
    ft_strlcpy(copy, input, len + 1);
    return (copy);
}

char **duplicate_matrix_without_quotes(char **matrix, int size)
{
    char **copy;
    int i;
    int len;

    i = 0;
    copy = malloc(sizeof(char *) * (size + 1));
    if (!copy)
        return (NULL);
    while (matrix[i] && i < size)
    {
        len = unquoted_strlen(matrix[i]);
        copy[i] = malloc(sizeof(char) * (len + 1));
        if (!copy)
        {
            ft_free_matrix(copy);
            return (NULL);
        }
        copy_without_quotes(copy[i], matrix[i], len);
        i++;
    }
    copy[i] = NULL;
    return (copy);
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
