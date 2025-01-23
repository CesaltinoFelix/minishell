#include "../minishell.h"

int ft_compare_str(const char *s1, const char *s2)
{
    int i;

    if (!s1 || !s2) 
        return (0);

    i = 0;
    while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'));
}

int count_valid_env(char **environ, char **matrix)
{
    int i;
    int j;
    int len;
    int found;

    i = 0;
    len = 0;
    while (environ[i])
    {
        j = 1;
        found = 0;
        while (matrix[j])
        {
            if (ft_compare_str(environ[i], matrix[j]) != 0)
            {
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
            len++;
        i++;
    }
    return (len);
}

void copy_valid_env(char **new_env, char **environ, char **matrix)
{
    int i;
    int j;
    int k;
    int found;

    i = 0;
    k = 0;
    while (environ[i])
    {
        j = 1;
        found = 0;
        while (matrix[j])
        {
            if (ft_compare_str(environ[i], matrix[j]) != 0)
            {
                found = 1;
                break;
            }
            j++;
        }
        if (!found)
            new_env[k++] = ft_strdup(environ[i]);
        i++;
    }
    new_env[k] = NULL;
}

int ft_unset(char **matrix)
{
    int len;
    char **new_env;
    extern char **environ;

    len = count_valid_env(environ, matrix);
    new_env = malloc(sizeof(char *) * (len + 1));
    if (!new_env)
    {
        perror("Erro ao alocar memória para new_env");
        return (1);
    }
    copy_valid_env(new_env, environ, matrix);
    environ = new_env;
    return (0);
}
