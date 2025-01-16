#include "../minishell.h"

int     ft_env(char **matrix)
{
        extern char **environ;
        int     i;

        i = -1;
        if (matrix[1] != NULL)
        {
                printf("too few arguments\n");
                return (2);
        }
        else
        {
                while (environ[++i])
                        printf("%s\n", environ[i]);
        }
        return (0);
}