#include "./../minishell.h"
#include <fcntl.h>
#include <unistd.h>

int ft_handle_redirections(t_minishell *shell)
{
    int i = 0;
    int fd = -1;

    shell->stdout_backup = dup(STDOUT_FILENO); // Salva o stdout original na estrutura

    while (shell->matrix[i])
    {
        if (strcmp(shell->matrix[i], ">") == 0 || strcmp(shell->matrix[i], ">>") == 0)
        {
            if (!shell->matrix[i + 1])
            {
                printf("Erro: nome de arquivo esperado após '%s'\n", shell->matrix[i]);
                return (-1);
            }

            // Abre o arquivo corretamente
            if (strcmp(shell->matrix[i], ">") == 0)
                fd = open(shell->matrix[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd = open(shell->matrix[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1)
            {
                perror("Erro ao abrir o arquivo");
                return (-1);
            }

            dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
            close(fd);

            // Remove os operadores de redirecionamento da matriz
            int j = i;
            while (shell->matrix[j + 2])
            {
                shell->matrix[j] = shell->matrix[j + 2];
                j++;
            }
            shell->matrix[j] = NULL; // Garante que a matriz termine corretamente
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
        dup2(shell->stdout_backup, STDOUT_FILENO); // Restaura stdout original
        close(shell->stdout_backup); // Fecha o descritor extra
        shell->stdout_backup = -1; // Resetamos para evitar problemas
    }
}
