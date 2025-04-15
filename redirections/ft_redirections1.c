/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:21 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 19:48:59 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int	handle_output_redir(t_minishell *shell, int i)
{
	int	flags;

	if (!shell->parsed_input[i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (handle_redirection_error(shell, i) == -1)
		return (-1);
	if (shell->stdout_backup == -1)
		shell->stdout_backup = dup(STDOUT_FILENO);
	flags = set_output_flags(shell->parsed_input[i]);
	return (open_output_file(shell, i, flags));
}

static int	handle_input_redir(t_minishell *shell, int i)
{
	int	fd;

	if (!shell->parsed_input[i + 1])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (handle_redirection_error(shell, i) == -1)
		return (-1);
	if (shell->stdin_backup == -1)
		shell->stdin_backup = dup(STDIN_FILENO);
	fd = open(shell->parsed_input[i + 1], O_RDONLY);
	if (fd == -1)
		return (printf("minishell: %s: No such file or directory\n",
				shell->parsed_input[i + 1]), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: error redirecting");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	aux_process_redirection(t_minishell *shell, int *i, int *res)
{
	if (is_output_redirection(shell->parsed_input[*i]))
	{
		if (handle_output_redir(shell, *i) == -1)
			return (-1);
		*res = 1;
	}
	else if (!ft_strcmp(shell->parsed_input[*i], "<"))
	{
		if (handle_input_redir(shell, *i) == -1)
			return (-1);
		*res = 1;
	}
	return (0);
}

static int	process_redirection(t_minishell *shell, int *i)
{
	char	temp_file[128];
	int		res;

	res = 0;
	if (aux_process_redirection(shell, i, &res) == -1)
		return (-1);
	else if (!ft_strcmp(shell->parsed_input[*i], "<<"))
	{
		ft_bzero(temp_file, sizeof(temp_file));
		if (ft_handle_heredoc(shell, *i, temp_file) == -1)
			return (-1);
		ft_memcpy(shell->last_heredoc_file, temp_file,
			sizeof(shell->last_heredoc_file));
	}
	else if (res == 0)
	{
		(*i)++;
		return (1);
	}
	remove_redirection(shell, *i);
	return (0);
}

int	ft_handle_redirections(t_minishell *shell)
{
	int	i;
	int	ret;

	i = 0;
	while (shell->parsed_input[i])
	{
		ret = process_redirection(shell, &i);
		if (ret == -1)
			return (-1);
		if (ret == 1)
			continue ;
	}
	if (shell->last_heredoc_file[0])
	{
		if (redirect_heredoc_input(shell, shell->last_heredoc_file) == -1)
			return (-1);
	}
	return (0);
}
