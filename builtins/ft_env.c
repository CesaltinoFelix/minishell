#include "../minishell.h"

int handle_env_command(t_minishell *shell)
{
    int i = 0;

    if (shell->matrix[1] != NULL)
    {
        printf("No such file or directory\n");
        return (127);
    }
    while (shell->env_var[i])
    {
        if (ft_strchr(shell->env_var[i], '='))
            printf("%s\n", shell->env_var[i]);
        i++;
    }
    return (0);
}
