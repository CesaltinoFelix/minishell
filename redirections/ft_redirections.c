#include "./../minishell.h"
#include <fcntl.h>
#include <unistd.h>

int ft_handle_redirections(t_minishell *shell)
{
    int i = 0;
    int fd = -1;

    shell->stdout_backup = dup(STDOUT_FILENO);

    while (shell->matrix[i])
    {
        if (strcmp(shell->matrix[i], ">") == 0 || strcmp(shell->matrix[i], ">>") == 0)
        {
            if (!shell->matrix[i + 1])
            {
                printf("erro de sintaxe próximo ao token inesperado `newline'\n");
                return (-1);
            }

            if (strcmp(shell->matrix[i], ">") == 0)
                fd = open(shell->matrix[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd = open(shell->matrix[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1)
            {
                perror("Erro ao abrir o arquivo");
                return (-1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            int j = i;
            while (shell->matrix[j + 2])
            {
                shell->matrix[j] = shell->matrix[j + 2];
                j++;
            }
            shell->matrix[j] = NULL;
            break;
        }
        i++;
    }

    return (0);
}

void ft_restore_stdout(t_minishell *shell)
{
    if (shell->stdout_backup != -1)
    {
        dup2(shell->stdout_backup, STDOUT_FILENO);
        close(shell->stdout_backup);
        shell->stdout_backup = -1;
    }
}
