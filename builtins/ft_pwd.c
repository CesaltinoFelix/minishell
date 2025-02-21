#include "../minishell.h"

int    ft_pwd(t_minishell *shell)
{
    char    buf[255];
    if (!ft_isalpha(shell->matrix[1][0]))
    {
        printf("%s: %s: invalid option\n", shell->matrix[0], shell->matrix[1]);
        return (2);
    }
    printf("%s\n", getcwd(buf, sizeof(buf)));
    return (0);
}