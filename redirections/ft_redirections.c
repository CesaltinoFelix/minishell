#include "./../minishell.h"

static int	ft_handle_output_redir(t_minishell *shell, int i)
{
	int		fd;
	int		flags;

	if (!shell->parsed_input[i + 1])
		return (printf("minishell: syntax error near unexpected token `newline''\n"), -1);
	flags = (strcmp(shell->parsed_input[i], ">") == 0)
		? (O_WRONLY | O_CREAT | O_TRUNC)
		: (O_WRONLY | O_CREAT | O_APPEND);
	fd = open(shell->parsed_input[i + 1], flags, 0644);
	if (fd == -1)
		return (perror("Erro ao abrir arquivo"), -1);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Erro ao redirecionar saída"), close(fd), -1);
	close(fd);
	return (0);
}

static int	ft_handle_input_redir(t_minishell *shell, int i)
{
	int	fd;

	if (!shell->parsed_input[i + 1])
		return (printf("minishell: syntax error near unexpected token `newline'\n"), -1);
	fd = open(shell->parsed_input[i + 1], O_RDONLY);
	if (fd == -1)
		return (perror("Erro ao abrir arquivo"), -1);
	shell->stdin_backup = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Erro ao redirecionar entrada"), close(fd), -1);
	close(fd);
	return (0);
}

int	ft_handle_redirections(t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->parsed_input[i])
	{
		if (!strcmp(shell->parsed_input[i], ">") || !strcmp(shell->parsed_input[i], ">>"))
		{
			if (ft_handle_output_redir(shell, i) == -1)
				return (-1);
		}
		else if (!strcmp(shell->parsed_input[i], "<"))
		{
			if (ft_handle_input_redir(shell, i) == -1)
				return (-1);
		}
		if (!strcmp(shell->parsed_input[i], "<") || !strcmp(shell->parsed_input[i], ">") ||
			!strcmp(shell->parsed_input[i], ">>"))
		{
			j = i;
			while (shell->parsed_input[j + 2])
			{
				shell->parsed_input[j] = shell->parsed_input[j + 2];
				j++;
			}
			shell->parsed_input[j] = NULL;
			shell->parsed_input[j + 1] = NULL;
			break ;
		}
		i++;
	}
	return (0);
}

void ft_restore_stdio(t_minishell *shell)
{
    if (shell->stdout_backup != -1)
    {
        dup2(shell->stdout_backup, STDOUT_FILENO);
        close(shell->stdout_backup);
        shell->stdout_backup = -1;
    }

    if (shell->stdin_backup != -1)
    {
        dup2(shell->stdin_backup, STDIN_FILENO);
        close(shell->stdin_backup);
        shell->stdin_backup = -1;
    }
}

