#include "../minishell.h"

void handle_echo_options(t_minishell *shell, int *print_newline, int *arg_index)
{
    int char_index;

    while (shell->matrix[*arg_index] && shell->matrix[*arg_index][0] == '-' 
           && shell->matrix[*arg_index][1] == 'n')
    {
        char_index = 2;
        while (shell->matrix[*arg_index][char_index] == 'n')
            char_index++;
        if (shell->matrix[*arg_index][char_index] == '\0')
            *print_newline = 0;
        else
            break;
        (*arg_index)++;
    }
}

int handle_echo_command(t_minishell *shell)
{
    int arg_index;
    int print_newline;

    arg_index = 1;
    print_newline = 1;
    handle_echo_options(shell, &print_newline, &arg_index);
    while (shell->matrix[arg_index])
    {
        printf("%s", shell->matrix[arg_index]);
        if (shell->matrix[arg_index + 1])
            printf(" ");
        arg_index++;
    }
    if (print_newline)
        printf("\n");
    return (0);
}
