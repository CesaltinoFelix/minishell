#include "../minishell.h"

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

void extract_key_value(t_minishell *shell, const char *arg)
{
    size_t i;

    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    shell->env.key = ft_strndup(arg, i);
    if (arg[i] == '=')
        shell->env.value = ft_strdup(arg + i + 1);
    else
        shell->env.value = NULL;
}

void print_error(const char *arg)
{
    printf("minishell: export: `%s`: not a valid identifier\n", arg);
}

char *create_env_var(t_minishell *shell)
{
    int len;
    char *new_var;

    len = ft_strlen(shell->env.key) + 2;
    if (shell->env.value)
        len += ft_strlen(shell->env.value);
    new_var = malloc(sizeof(char) * len);
    if (!new_var)
        return (NULL);
    ft_strlcpy(new_var, shell->env.key, len);
    if (shell->env.value)
    {
        ft_strlcat(new_var, "=", len);
        ft_strlcat(new_var, shell->env.value, len);
    }
    return (new_var);
}

void add_env_var(t_minishell *shell, char *new_var)
{
    int i;
    char **new_environ;

    i = -1;
    while (shell->env_var[++i])
        ;
    new_environ = malloc(sizeof(char *) * (i + 2));
    if (!new_environ)
        return;
    i = -1;
    while (shell->env_var[++i])
        new_environ[i] = ft_strdup(shell->env_var[i]);
    new_environ[i] = ft_strdup(new_var);
    new_environ[i + 1] = NULL;
    ft_free_matrix(shell->env_var);
    shell->env_var = new_environ;
}

int ft_update_aux(const char *env_var, const char *key, size_t key_len)
{
    return (ft_strncmp(env_var, key, key_len) == 0 &&
            (env_var[key_len] == '=' || env_var[key_len] == '\0'));
}

void update_or_add_env(t_minishell *shell)
{
    int i;
    char *new_var;

    i = -1;
    shell->env.equal_sign = ft_strchr(shell->env.key, '=');
    if (shell->env.equal_sign != NULL)
        shell->env.key_len = shell->env.equal_sign - shell->env.key;
    else
        shell->env.key_len = ft_strlen(shell->env.key);
    while (shell->env_var[++i])
    {
        if (ft_update_aux(shell->env_var[i], shell->env.key, shell->env.key_len))
        {
            new_var = create_env_var(shell);
            if (shell->env.value)
            {
                free(shell->env_var[i]);
                shell->env_var[i] = new_var;
            }
            return;
        }
    }
    new_var = create_env_var(shell);
    if (new_var)
        add_env_var(shell, new_var);
}

void list_env(t_minishell *shell)
{
    int i;
    char *equal_sign;
    char **print_env_order;

    i = -1;
    print_env_order = ft_cpy_env(shell->env_var);
    ft_sort_string_matrix(print_env_order);
    while (print_env_order[++i])
    {
        equal_sign = ft_strchr(print_env_order[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            printf("declare -x %s=\"%s\"\n", print_env_order[i], equal_sign + 1);
            *equal_sign = '=';
        }
        else
            printf("declare -x %s\n", print_env_order[i]);
    }
}

int ft_export(t_minishell *shell)
{
    int i;

    i = 1;
    if (!shell->matrix[1])
        list_env(shell);
    else
    {
        while (shell->matrix[i])
        {
            if (is_valid_identifier(shell->matrix[i]))
            {
                extract_key_value(shell, shell->matrix[i]);
                update_or_add_env(shell);
                free(shell->env.key);
                free(shell->env.value);
            }
            else
                print_error(shell->matrix[i]);
            i++;
        }
    }
    return (0);
}
