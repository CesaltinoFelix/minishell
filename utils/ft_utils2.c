/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:08 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 21:12:56 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_append_mode(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
	{
		if (ft_strcmp(cmd_args[i], ">>") == 0)
		{
			return (O_WRONLY | O_CREAT | O_APPEND);
		}
		i++;
	}
	return (O_WRONLY | O_CREAT | O_TRUNC);
}

int	handle_builtin_commands(t_minishell *shell)
{
	if (ft_strcmp(shell->parsed_input[0], "echo") == 0)
		return (handle_echo_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "cd") == 0)
		return (handle_cd_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "pwd") == 0)
		return (handle_pwd_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "export") == 0)
		return (handle_export_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "unset") == 0)
		return (handle_unset_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "env") == 0)
		return (handle_env_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "exit") == 0)
	{
		handle_exit_command(shell);
		return (shell->exit_status);
	}
	return (-1);
}

void	handle_child_process(t_minishell *shell, t_pipeline *cmd,
	int prev_pipe_in, int pipes[2])
{
	char	**parsed_input;

	parsed_input = shell->parsed_input;
	setup_child_io(cmd, prev_pipe_in, pipes);
	shell->parsed_input = cmd->cmd_args;
	if (is_builtin(cmd->cmd_args[0]))
		execute_command(shell);
	else
		execute_external_command(shell);
	ft_free_matrix(shell->parsed_input);
	shell->parsed_input = parsed_input;
	exit(shell->exit_status);
}
