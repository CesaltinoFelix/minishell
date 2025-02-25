#include "../minishell.h"

int is_valid_numeric_argument(const char *str)
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
    return (1);
}

void handle_exit_command(t_minishell *shell)
{
    long numeric_exit_code;

    printf("exit\n");
    if (shell->matrix[1])
    {
        if (!is_valid_numeric_argument(shell->matrix[1]))
        {
            printf("minishell: exit: %s: numeric argument required\n", shell->matrix[1]);
            shell->status = 2;
        }
        else if (shell->matrix[2])
        {
            printf("minishell: exit: too many arguments\n");
            shell->status = 1;
            return;
        }
        else
        {
            numeric_exit_code = ft_atoi(shell->matrix[1]);
            shell->status = (numeric_exit_code & 255);
        }
    }
    check_to_free(shell);
    exit(shell->status);
}
