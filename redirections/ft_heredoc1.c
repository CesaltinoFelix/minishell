/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/24 12:56:16 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_heredoc_interrupted;

int	read_heredoc_input(int fd, t_minishell *shell, int i)
{
	char	*line;

	while (1)
	{
		if (g_heredoc_interrupted)
			return (-1);
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document at line 11 delimited by end-of-file"
				" (wanted `%s')\n", shell->parsed_input[i + 1]);
			break ;
		}
		if (ft_strcmp(line, shell->parsed_input[i + 1]) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	process_heredoc(t_minishell *shell, int fd, int i, char *file)
{
	setup_heredoc_signals();
	if (read_heredoc_input(fd, shell, i) == -1)
	{
		unlink(file);
		exit(130);
	}
	exit(0);
}

int	handle_heredoc_child(int fd, t_minishell *shell, int i, char *file)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd);
		unlink(file);
		return (-1);
	}
	if (pid == 0)
		process_heredoc(shell, fd, i, file);
	close(fd);
	return (pid);
}

int	redirect_heredoc_input(t_minishell *shell, char *file)
{
	int	fd;

	if (shell->stdin_backup == -1)
		shell->stdin_backup = dup(STDIN_FILENO);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		printf("error: could not open heredoc file\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("error: dup2 failed\n");
		return (close(fd), -1);
	}
	close(fd);
	unlink(file);
	return (0);
}

int	ft_handle_heredoc(t_minishell *shell, int i)
{
	int		fd;
	int		pid;
	char	file[128];

	g_heredoc_interrupted = 0;
	ignore_sigint();
	fd = create_temp_file(file);
	if (!shell->parsed_input[i + 1])
		return (printf(\
"minishell: syntax error near unexpected token `newline'\n"), -1);
	if (fd == -1)
		return (-1);
	pid = handle_heredoc_child(fd, shell, i, file);
	if (pid == -1)
		return (-1);
	if (wait_for_heredoc(shell, pid, file) == -1)
		return (-1);
	restore_sigint();
	return (redirect_heredoc_input(shell, file));
}
