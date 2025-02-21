#include "../minishell.h"

int ft_is_numeric(const char *str)
{
    if (!str || !*str)
        return 0;
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (!ft_isdigit(*str))
            return 0;
        str++;
    }
    return (2);
}

void ft_exit(t_minishell *shell)
{
    int exit_code;
    
    exit_code = shell->last_exit_code;
    printf("exit\n");
    if (shell->matrix && shell->matrix[1])
    {
        if (!ft_is_numeric(shell->matrix[1]))
        {
            printf("minishell: exit: %s: numeric argument required\n", shell->matrix[1]);
            exit_code = 255;
        }
        else if (shell->matrix[2])
        {
            perror("minishell: exit: too many arguments\n");
            shell->last_exit_code = 1;
            return;
        }
        else
            exit_code = ft_atoi(shell->matrix[1]);
    }
    check_to_free(shell);
    exit(exit_code);
}
