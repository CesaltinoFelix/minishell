#include "../minishell.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

extern char **environ;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Protótipos de funções
t_env *create_env_node(char *env_str);
t_env *init_env(char **environ);
void print_env(t_env *env);
void free_env(t_env *env);
void list_env(t_env *env);
int is_valid_identifier(const char *str);
void add_or_update_env(char *arg, t_env **env);
char *get_key(char *arg);
char *get_value(char *arg);
void print_error(char *arg);
int ft_export(char **args);
char *ft_strdup(const char *s1);
char *ft_substr(const char *s, unsigned int start, size_t len);
char *ft_strchr(const char *s, int c);
int ft_isalpha(int c);
int ft_isalnum(int c);
int ft_strcmp(const char *s1, const char *s2);
void find_variable(const char *var_name);
// Implementação das funções
t_env *create_env_node(char *env_str)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);

    char *equal_sign = strchr(env_str, '=');
    if (!equal_sign)
    {
        free(node);
        return (NULL);
    }

    size_t key_len = equal_sign - env_str;
    node->key = strndup(env_str, key_len);
    node->value = strdup(equal_sign + 1);
    node->next = NULL;

    return (node);
}

t_env *init_env(char **environ)
{
    t_env *head = NULL;
    t_env *current = NULL;

    for (int i = 0; environ[i] != NULL; i++)
    {
        t_env *new_node = create_env_node(environ[i]);
        if (!new_node)
            continue;

        if (!head)
            head = new_node;
        else
            current->next = new_node;

        current = new_node;
    }

    return (head);
}

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

void list_env(t_env *env)
{
    t_env *tmp = env;
    while (tmp)
    {
        printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value ? tmp->value : "");
        tmp = tmp->next;
    }
}

int is_valid_identifier(const char *str)
{
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    for (int i = 1; str[i] && str[i] != '='; i++)
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
    return (1);
}

void add_or_update_env(char *arg, t_env **env)
{
    char *key = get_key(arg);
    char *value = get_value(arg);
    t_env *tmp = *env;

    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = value; 
            free(key);
            return;
        }
        tmp = tmp->next;
    }
    
    t_env *new_node = malloc(sizeof(t_env));
    new_node->key = key;
    new_node->value = value;
    new_node->next = *env;
    *env = new_node;
}

char *get_key(char *arg)
{
    int i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    return (ft_substr(arg, 0, i));
}

char *get_value(char *arg)
{
    char *equal_sign = ft_strchr(arg, '=');
    if (!equal_sign)
        return (NULL);
    return (ft_strdup(equal_sign + 1));
}

void print_error(char *arg)
{
    fprintf(stderr, "minishell: export: `%s`: not a valid identifier\n", arg);
}



void find_variable(const char *var_name)
{
    char *value = getenv(var_name);
    if (value)
        printf("%s=%s\n", var_name, value);
    else
        printf("Variável %s não encontrada.\n", var_name);
}



int ft_export(char **args)
{
    t_env *env = init_env(environ);
    if (!args[1]) 
        list_env(env);
    else
    { 
        for (int i = 1; args[i]; i++)
        {
            if (is_valid_identifier(args[i]))
                add_or_update_env(args[i], &env);
            else
                print_error(args[i]); 
        }
    }

    print_env(env);
    printf("\nBuscando a variável PATH:\n");
    find_variable("CEL");
    free_env(env);
    return (0);
}
