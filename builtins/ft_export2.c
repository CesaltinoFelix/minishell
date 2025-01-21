#include "../minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern char **environ;

// Protótipos de funções
int is_valid_identifier(const char *str);
char *get_key(const char *arg);
char *get_value(const char *arg);
void print_error(const char *arg);
void update_or_add_env(const char *key, const char *value);
void remove_env(const char *key);
void list_env(void);
int ft_export(char **args);

// Implementação das funções

int is_valid_identifier(const char *str)
{
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    for (int i = 1; str[i] && str[i] != '='; i++)
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
    return (1);
}

char *get_key(const char *arg)
{
    size_t i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    return ft_substr(arg, 0, i);
}

char *get_value(const char *arg)
{
    const char *equal_sign = ft_strchr(arg, '=');
    if (!equal_sign)
        return NULL;
    return ft_strdup(equal_sign + 1);
}

void print_error(const char *arg)
{
    fprintf(stderr, "minishell: export: `%s`: not a valid identifier\n", arg);
}

void update_or_add_env(const char *key, const char *value)
{
    extern char **environ;
    size_t key_len = strlen(key);
    char *new_var = malloc(strlen(key) + strlen(value) + 2);
    if (!new_var)
    {
        perror("Erro ao alocar memória");
        return;
    }
    sprintf(new_var, "%s=%s", key, value);

    for (int i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], key, key_len) == 0 && environ[i][key_len] == '=')
        {
            free(environ[i]);
            environ[i] = new_var;
            return;
        }
    }

    // Adicionar nova variável
    for (int i = 0; ; i++)
    {
        if (!environ[i])
        {
            environ = realloc(environ, sizeof(char *) * (i + 2));
            if (!environ)
            {
                perror("Erro ao realocar memória");
                free(new_var);
                return;
            }
            environ[i] = new_var;
            environ[i + 1] = NULL;
            return;
        }
    }
}

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

void list_env(void)
{
    extern char **environ;
    for (int i = 0; environ[i]; i++)
        printf("declare -x %s\n", environ[i]);
}

int ft_export(char **args)
{
    if (!args[1])
    {
        list_env();
    }
    else
    {
        for (int i = 1; args[i]; i++)
        {
            if (is_valid_identifier(args[i]))
            {
                char *key = get_key(args[i]);
                char *value = get_value(args[i]);

                if (value)
                    update_or_add_env(key, value);
                // else
                //     remove_env(key);

                free(key);
                free(value);
            }
            else
            {
                print_error(args[i]);
            }
        }
    }
    return 0;
}
