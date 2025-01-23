#include "../minishell.h"

char    **ft_cpy_env()
{
    int i;
    char    **new_env;
    extern char **environ;

    i = -1;
    while (environ[++i]);
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return (NULL);
    i = -1;
    while (environ[++i])
    {
        new_env[i] = ft_strdup(environ[i]);
    }
    new_env[i] = NULL;
    return (new_env);
}

void init_env(t_env *env)
{
    int i;
    int j;
    extern char **environ;
    
    i = -1;
    j = -1;
    while (environ[++i]);
    env->count = i;
    env->flags = malloc(sizeof(int) * (i + 1));
    if (!env->flags)
        return;
    while (++j < i)
        env->flags[j] = 0;
    env->variables = environ;
    env->key = NULL;
    env->value = NULL;
}

int is_valid_identifier(const char *str)
{
    int i;
    
    i = 0;
    if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            break;
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void extract_key_value(t_env *env, const char *arg)
{
    size_t  i;
    
    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    env->key = ft_strndup(arg, i);
    if (arg[i] == '=')
        env->value = ft_strdup(arg + i + 1);
    else
        env->value = NULL;
}

void print_error(const char *arg)
{
    printf("minishell: export: `%s`: not a valid identifier\n", arg);
}

char *create_env_var(t_env *env)
{
    int len;
    
    len = strlen(env->key) + 2;
    if (env->value)
        len += strlen(env->value);
    char *new_var = malloc(len);
    if (!new_var)
        return NULL;
    ft_strlcpy(new_var, env->key, len);
    if (env->value)
    {
        ft_strlcat(new_var, "=", len);
        ft_strlcat(new_var, env->value, len);
    }
    return new_var;
}

void add_env_var(t_env *env, char *new_var)
{
    int i;
    int *new_flag;
    char **new_environ;
    extern char **environ;

    i = -1;
    while (env->variables[++i]);
    new_environ = malloc(sizeof(char *) * (i + 2));
    new_flag = malloc(sizeof(int) * (i + 2));
    if (!new_environ || !new_flag)
        return;
    i = -1;
    while (env->variables[++i])
    {
        new_environ[i] = env->variables[i];
        new_flag[i] = env->flags[i];
    }
    new_environ[i] = new_var;
    new_flag[i] = 1;
    new_environ[i + 1] = NULL;
    new_flag[i + 1] = -1;
    env->variables = new_environ;
    env->flags = new_flag;
    environ = new_environ;
}

void update_or_add_env(t_env *env)
{
    int i;
    char *new_var = NULL;

    i = -1;
    while (env->variables[++i])
    {
        if (ft_compare_str(env->variables[i], env->key) != 0)
        {
            new_var = create_env_var(env);
            if (env->value)
            {
                if (env->flags[i] == 0)
                    env->variables[i] = new_var;
                else
                {
                    free(env->variables[i]);
                    env->variables[i] = new_var;
                }
            }
            return;
        }
    }
    new_var = create_env_var(env);
    if (new_var)
        add_env_var(env, new_var);
}

void list_env(t_env *env)
{
    int i;
    char *equal_sign;
    char **print_order = ft_cpy_env();
    (void)env;

    i = 0;
    ft_sort_string_matrix(print_order);
    while (print_order[i])
    {
        equal_sign = strchr(print_order[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            printf("declare -x %s=\"%s\"\n", print_order[i], equal_sign + 1);
            *equal_sign = '=';
        }
        else
            printf("declare -x %s\n", print_order[i]);
        i++;
    }
}

int ft_export(char **args)
{
    int i;
    t_env env;

    i = 1;
    init_env(&env);
    if (!args[1])
        list_env(&env);
    else
    {
        while (args[i])
        {
            if (is_valid_identifier(args[i]))
            {
                extract_key_value(&env, args[i]);
                if (env.key)
                    update_or_add_env(&env);
                free(env.key);
                free(env.value);
            }
            else
                print_error(args[i]);
            i++;
        }
    }
    return (0);
}
