#include "../minishell.h"

int ft_env(t_minishell *shell)
{
        int i;

        i = -1;
        if (shell->matrix[1] != NULL)
        {
                printf("error: has option or argument\n");
                return (1);
        }
        else
        {
                while (shell->env_var[++i])
                {
                        if (ft_strchr(shell->env_var[i], '='))
                                printf("%s\n", shell->env_var[i]);
                }
        }
        return (0);
}