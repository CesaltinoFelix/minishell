#include "../minishell.h"

void ft_cd(char **matrix)
{
    if (matrix[2] != NULL)
        printf("%s: too many arguments\n", matrix[0]);
    else if (chdir(matrix[1]) == 0)
    {
    }
    else
        printf("%s: %s: No such file or directory\n", matrix[0], matrix[1]);
}