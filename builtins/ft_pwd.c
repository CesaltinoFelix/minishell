#include "../minishell.h"

int handle_pwd_command(t_minishell *shell)
{
    char current_directory[255];

    if (shell->matrix[1])  
    {
        if (!ft_isalpha(shell->matrix[1][0]))
        {
            printf("%s: %s: invalid option\n", shell->matrix[0], shell->matrix[1]);
            return (2);
        }
    }
    if (getcwd(current_directory, sizeof(current_directory)))
        printf("%s\n", current_directory);
    return (0);
}
