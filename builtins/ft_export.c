#include "../minishell.h"

static void extract_env_key_value(t_minishell *shell, const char *arg)
{
    size_t equal_sign_pos;

    equal_sign_pos = 0;
    while (arg[equal_sign_pos] && arg[equal_sign_pos] != '=')
        equal_sign_pos++;
    shell->env.key = ft_strndup(arg, equal_sign_pos);
    if (arg[equal_sign_pos] == '=')
        shell->env.value = ft_strdup(arg + equal_sign_pos + 1);
    else
        shell->env.value = NULL;
}

static char *create_env_var_string(t_minishell *shell)
{
    int total_length;
    char *env_var;

    total_length = ft_strlen(shell->env.key) + 2;
    if (shell->env.value)
        total_length += ft_strlen(shell->env.value);
    env_var = malloc(sizeof(char) * total_length);
    if (!env_var)
        return (NULL);
    ft_strlcpy(env_var, shell->env.key, total_length);
    if (shell->env.value)
    {
        ft_strlcat(env_var, "=", total_length);
        ft_strlcat(env_var, shell->env.value, total_length);
    }
    return (env_var);
}

static void add_env_var_to_array(t_minishell *shell, char *new_var)
{
    int i;
    char **new_env;

    i = 0;
    while (shell->env_var[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return;
    i = -1;
    while (shell->env_var[++i])
        new_env[i] = ft_strdup(shell->env_var[i]);
    new_env[i] = ft_strdup(new_var);
    new_env[i + 1] = NULL;
    ft_free_matrix(shell->env_var);
    shell->env_var = new_env;
}

void update_or_add_env_var(t_minishell *shell)
{
    int i;
    char *new_var;

    i = -1;
    shell->env.equal_sign = ft_strchr(shell->env.key, '=');
    if (shell->env.equal_sign)
        shell->env.key_len = shell->env.equal_sign - shell->env.key;
    else
        shell->env.key_len = ft_strlen(shell->env.key);
    while (shell->env_var[++i])
    {
        if (is_env_var_match(shell->env_var[i], shell->env.key, shell->env.key_len))
        {
            new_var = create_env_var_string(shell);
            if (shell->env.value)
            {
                free(shell->env_var[i]);
                shell->env_var[i] = new_var;
            }
            return;
        }
    }
    new_var = create_env_var_string(shell);
    if (new_var)
        add_env_var_to_array(shell, new_var);
}

int handle_export_command(t_minishell *shell)
{
    int i;

    i = 1;
    if (!shell->matrix[1])
        print_sorted_env_vars(shell);
    else
    {
        while (shell->matrix[i])
        {
            if (is_valid_env_var_name(shell->matrix[i]))
            {
                extract_env_key_value(shell, shell->matrix[i]);
                update_or_add_env_var(shell);
                free(shell->env.key);
                free(shell->env.value);
            }
            else
                return (print_invalid_identifier_error(shell->matrix[i]), 1);
            i++;
        }
    }
    return (0);
}
