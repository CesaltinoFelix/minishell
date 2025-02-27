#include "../minishell.h"

static void extract_env_key_value(t_minishell *shell, const char *arg)
{
    size_t equal_sign_pos;

    equal_sign_pos = 0;
    while (arg[equal_sign_pos] && arg[equal_sign_pos] != '=')
        equal_sign_pos++;
    shell->env_var.key = ft_strndup(arg, equal_sign_pos);
    if (arg[equal_sign_pos] == '=')
        shell->env_var.value = ft_strdup(arg + equal_sign_pos + 1);
    else
        shell->env_var.value = NULL;
}

static char *create_env_var_string(t_minishell *shell)
{
    int total_length;
    char *var_name;

    total_length = ft_strlen(shell->env_var.key) + 2;
    if (shell->env_var.value)
        total_length += ft_strlen(shell->env_var.value);
    var_name = malloc(sizeof(char) * total_length);
    if (!var_name)
        return (NULL);
    ft_strlcpy(var_name, shell->env_var.key, total_length);
    if (shell->env_var.value)
    {
        ft_strlcat(var_name, "=", total_length);
        ft_strlcat(var_name, shell->env_var.value, total_length);
    }
    return (var_name);
}

static void add_env_var_to_array(t_minishell *shell, char *new_var)
{
    int i;
    char **new_envarion;

    i = 0;
    while (shell->env_variables[i])
        i++;
    new_envarion = malloc(sizeof(char *) * (i + 2));
    if (!new_envarion)
        return;
    i = -1;
    while (shell->env_variables[++i])
        new_envarion[i] = ft_strdup(shell->env_variables[i]);
    new_envarion[i] = ft_strdup(new_var);
    new_envarion[i + 1] = NULL;
    free(new_var);
    ft_free_matrix(shell->env_variables);
    shell->env_variables = new_envarion;
}

void update_or_add_env_var(t_minishell *shell)
{
    int i;
    char *new_var;

    i = -1;
    shell->env_var.equal_sign = ft_strchr(shell->env_var.key, '=');
    if (shell->env_var.equal_sign)
        shell->env_var.key_len = shell->env_var.equal_sign - shell->env_var.key;
    else
        shell->env_var.key_len = ft_strlen(shell->env_var.key);
    while (shell->env_variables[++i])
    {
        if (is_env_var_match(shell->env_variables[i], shell->env_var.key, shell->env_var.key_len))
        {
            new_var = create_env_var_string(shell);
            if (shell->env_var.value)
            {
                free(shell->env_variables[i]);
                shell->env_variables[i] = new_var;
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
    int flag;

    i = 1;
    flag = 0;
    if (!shell->parsed_input[1])
        print_sorted_env_vars(shell);
    else
    {
        while (shell->parsed_input[i])
        {
            if (is_valid_env_var_name(shell->parsed_input[i]))
            {
                extract_env_key_value(shell, shell->parsed_input[i]);
                update_or_add_env_var(shell);
                free(shell->env_var.key);
                free(shell->env_var.value);
            }
            else
            {
                print_invalid_identifier_error(shell->parsed_input[i]);
                flag = 1;
            }
            i++;
        }
    }
    return (flag);
}
