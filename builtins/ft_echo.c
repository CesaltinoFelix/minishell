#include "../minishell.h"

static int ft_echo_with_n(t_minishell *shell)
{
    int i;
    int j;

    i = 1;
    while (shell->matrix[i])
    {
        if (shell->matrix[i][0] == '-' && shell->matrix[i][1] == 'n')
        {
            j = 2;
            while (shell->matrix[i][j] == 'n')
                j++;
            if (shell->matrix[i][j] == '\0')
                return (0);
        }
        else
            break;
        i++;
    }
    return (1);
}

void    ft_aux_echo(t_minishell *shell, int *i)
{
    int j;

    while (shell->matrix[*i] && shell->matrix[*i][0] == '-' && shell->matrix[*i][1] == 'n')
    {
        j = 2;
        while (shell->matrix[*i][j] == 'n')
            j++;
        if (shell->matrix[*i][j] != '\0')
            break;
        (*i)++;
    }
}

int ft_echo(t_minishell *shell)
{
    int i = 1;
    int new_line = 1;

    if (ft_echo_with_n(shell) == 0)
    {
       new_line = 0;
       ft_aux_echo(shell, &i);
    }
    while (shell->matrix[i])
    {
        printf("%s", shell->matrix[i]);
        if (shell->matrix[i + 1])
            printf(" ");
        i++;
    }
    if (new_line)
        printf("\n");
    return (0);
}