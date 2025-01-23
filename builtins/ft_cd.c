#include "../minishell.h"

int ft_cd(char **matrix)
{
    char buf[255];
    char *update_env[3];

    update_env[0] = ft_strdup("export");
    update_env[1] = ft_strjoin("OLDPWD=", getcwd(buf, sizeof(buf)));
    update_env[2] = NULL;
    if (matrix[2] != NULL)
        printf("%s: too many arguments\n", matrix[0]);
    else if (chdir(matrix[1]) == 0)
    {
        ft_export(update_env);
        update_env[1] = ft_strjoin("PWD=", getcwd(buf, sizeof(buf)));
        ft_export(update_env);
    }
    else if (matrix[1] == NULL)
        return (0);
    else
        printf("%s: %s: No such file or directory\n", matrix[0], matrix[1]);
    return (0);
}