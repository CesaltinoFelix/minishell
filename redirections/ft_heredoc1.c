/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/04/15 17:39:02 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	read_heredoc_input(int fd, t_minishell *shell, int i)
{
	char		*line;
	extern int	g_status;

	while (1)
	{
		if (g_status)
			return (-1);
		line = readline("> ");
		if (!line)
		{
			printf("warning: here-document at line 11 delimited"
				" by end-of-file (wanted `%s')\n", shell->parsed_input[i + 1]);
			free(line);
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

int	ft_handle_heredoc(t_minishell *shell, int i, char *heredoc_path)
{
	int			fd;
	int			pid;
	char		file[128];
	extern int	g_status;

	g_status = 0;
	ignore_sigint();
	fd = create_temp_file(file);
	if (!shell->parsed_input[i + 1])
		return (printf("minishell: syntax error near"
				" unexpected token `newline'\n"), -1);
	if (fd == -1)
		return (-1);
	pid = handle_heredoc_child(fd, shell, i, file);
	if (pid == -1)
		return (-1);
	if (wait_for_heredoc(shell, pid, file) == -1)
	{
		signal(SIGINT, sigint_handler);
		return (-1);
	}
	signal(SIGINT, sigint_handler);
	ft_memcpy(heredoc_path, file, 128);
	return (0);
}
