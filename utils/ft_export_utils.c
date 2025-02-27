#include "../minishell.h"

void print_sorted_env_vars(t_minishell *shell)
{
    int i;
    char *equal_sign;
    char **sorted_env;

    i = 0;
    sorted_env = ft_cpy_env_variables(shell->env_variables);
    ft_sort_string_matrix(sorted_env);
    while (sorted_env[i])
    {
        equal_sign = ft_strchr(sorted_env[i], '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            printf("declare -x %s=\"%s\"\n", sorted_env[i], equal_sign + 1);
            *equal_sign = '=';
        }
        else
            printf("declare -x %s\n", sorted_env[i]);
        i++;
    }
    ft_free_matrix(sorted_env);
}
