#include "../minishell.h"

int ft_env(char **matrix)
{
        int     i;
        extern char     **environ;

        i = -1;
        if (matrix[1] != NULL)
        {
                perror("too few arguments\n");
                return (2);
        }
        else
        {
                while (environ[++i])
                {
                        if (ft_strchr(environ[i], '='))
                                printf("%s\n", environ[i]);
                }
        }
        return (0);
}