/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/27 12:23:34 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	init_cmd(t_pipeline *cmd, char **input, int i)
{
	cmd->cmd_args = &input[i];
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
}

char	*get_output_file(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (ft_strcmp(cmd_args[i], ">") == 0 || \
ft_strcmp(cmd_args[i], ">>") == 0)
		{
			if (cmd_args[i + 1])
				return (cmd_args[i + 1]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

char	*get_input_file(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (ft_strcmp(cmd_args[i], "<") == 0)
		{
			if (cmd_args[i + 1])
				return (cmd_args[i + 1]);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

void	remove_redirection_tokens(char **cmd_args, char *token)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (ft_strcmp(cmd_args[i], token) == 0)
		{
			free(cmd_args[i]);
			free(cmd_args[i + 1]);
			while (cmd_args[i + 2])
			{
				cmd_args[i] = cmd_args[i + 2];
				i++;
			}
			cmd_args[i] = NULL;
			cmd_args[i + 1] = NULL;
			break ;
		}
		i++;
	}
}
