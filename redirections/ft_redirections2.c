/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:21 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 17:12:40 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	handle_redirection_error(t_minishell *shell, int i)
{
	if (!ft_strcmp(shell->parsed_input[i + 1], ">")
		|| !ft_strcmp(shell->parsed_input[i + 1], "<")
		|| !ft_strcmp(shell->parsed_input[i + 1], ">>")
		|| !ft_strcmp(shell->parsed_input[i + 1], "<<"))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			shell->parsed_input[i + 1]);
		return (-1);
	}
	return (0);
}

int	set_output_flags(char *redir_type)
{
	if (!ft_strcmp(redir_type, ">"))
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (O_WRONLY | O_CREAT | O_APPEND);
}

int	open_output_file(t_minishell *shell, int i, int flags)
{
	int fd;

	fd = open(shell->parsed_input[i + 1], flags, 0644);
	if (fd == -1)
	{
		perror("minishell: error opening file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: error redirecting");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}