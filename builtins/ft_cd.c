#include "../minishell.h"
#include <sys/types.h>
#include <dirent.h>

void    ft_cd(char **matrix)
{
    char    buf[255];

    if (matrix[2] != NULL)
        printf("%s: too many arguments\n", matrix[0]);
    else if (chdir(matrix[1]) == 0)
        printf("currently directory now: %s\n", getcwd(buf, sizeof(buf)));
    else
        printf("%s: %s: No such file or directory\n", matrix[0], matrix[1]);
}