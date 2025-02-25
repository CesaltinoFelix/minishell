#include "../minishell.h"

static int is_env_var_unset(char *var_name, t_minishell *shell)
{
    int i = 1;

    while (shell->matrix[i])
    {
        shell->env.key = shell->matrix[i];
        if (is_env_var_match(var_name, shell->env.key, ft_strlen(shell->env.key)))
            return (1);
        i++;
    }
    return (0);
}

static int count_remaining_env_vars(t_minishell *shell)
{
    int count = 0;
    int i = 0;

    while (shell->env_var[i])
    {
        if (!is_env_var_unset(shell->env_var[i], shell))
            count++;
        i++;
    }
    return (count);
}

static int allocate_new_env(t_minishell *shell, char ***new_env)
{
    int valid_count;
    
    valid_count = count_remaining_env_vars(shell);
    *new_env = malloc(sizeof(char *) * (valid_count + 1));
    return (*new_env == NULL);
}

int handle_unset_command(t_minishell *shell)
{
    int old_index;
    int new_index;
    char **new_env;

    old_index = -1;
    new_index = -1;
    if (validate_unset_option(shell->matrix) || allocate_new_env(shell, &new_env))
        return (2);
    while (shell->env_var[++old_index])
    {
        if (!is_env_var_unset(shell->env_var[old_index], shell))
        {
            new_env[++new_index] = ft_strdup(shell->env_var[old_index]);
            if (!new_env[new_index])
            {
                ft_free_matrix(new_env);
                return (2);
            }
        }
    }
    new_env[++new_index] = NULL;
    ft_free_matrix(shell->env_var);
    shell->env_var = new_env;
    return (0);
}
