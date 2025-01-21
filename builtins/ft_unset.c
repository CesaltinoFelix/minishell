#include "../minishell.h"

void remove_env(const char *key)
{
    extern char **environ;
    size_t key_len = strlen(key);

    for (int i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], key, key_len) == 0 && environ[i][key_len] == '=')
        {
            free(environ[i]);
            for (int j = i; environ[j]; j++)
                environ[j] = environ[j + 1];
            return;
        }
    }
}

int    ft_unset(char **matrix)
{
    printf("test: %s\n", matrix[0]);
    return (0);
}