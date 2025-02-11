#include "../minishell.h"

static int compare_names(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'))
        return (1);
    return (0);
}

static int should_remove(char *env_var, t_minishell *shell)
{
    int i;
    char *matrix_var;

    i = 0;
    while (shell->matrix[i] != NULL)
    {
        matrix_var = shell->matrix[i];
        if (!is_valid_identifier(matrix_var))
        {
            i++;
            continue;
        }
        if (compare_names(env_var, matrix_var))
        {
            if (ft_strchr(matrix_var, '=') == NULL)
                return (1);
            if (ft_strcmp(env_var, matrix_var) == 0)
                return (1);
        }
        i++;
    }
    return (0);
}

static int count_valid_envs(t_minishell *shell)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (shell->env_var[i] != NULL)
    {
        if (!should_remove(shell->env_var[i], shell))
            count++;
        i++;
    }
    return (count);
}

int ft_aux_unset(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        if (!is_valid_identifier(str[i]))
        {
            printf("unset: `%s`: not a valid identifier\n", str[i]);
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_unset_aux2(t_minishell *shell, char ***new_env)
{
    int valid_count;
    
    valid_count = count_valid_envs(shell);
    *new_env = malloc(sizeof(char *) * (valid_count + 1));
    if (*new_env == NULL)
        return (1);
    return (0);
}

int ft_unset(t_minishell *shell)
{
    int i;
    int k;
    char **new_env;
    
    i = -1;
    k = -1;
    if (ft_aux_unset(shell->matrix) != 0 || ft_unset_aux2(shell, &new_env))
        return (1);
    while (shell->env_var[++i] != NULL)
    {
        if (!should_remove(shell->env_var[i], shell))
        {
            new_env[++k] = ft_strdup(shell->env_var[i]);
            if (new_env[k] == NULL)
                return (ft_free_matrix(new_env), 1);
        }
    }
    new_env[k] = NULL;
    ft_free_matrix(shell->env_var);
    shell->env_var = new_env;
    return (0);
}

