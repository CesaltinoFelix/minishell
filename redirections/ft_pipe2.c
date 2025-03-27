/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/27 13:30:32 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipeline	*split_commands(t_minishell *shell, int *cmd_count)
{
	int			i;
	int			j;
	t_pipeline	*cmds;

	i = 0;
	j = 0;
	cmds = malloc(sizeof(t_pipeline) * 10);
	while (shell->parsed_input[i])
	{
		init_cmd(&cmds[j], shell->parsed_input, i);
		while (shell->parsed_input[i] && \
			ft_strcmp(shell->parsed_input[i], "|") != 0)
			i++;
		if (shell->parsed_input[i] && \
			ft_strcmp(shell->parsed_input[i], "|") == 0)
		{
			shell->parsed_input[i] = NULL;
			i++;
		}
		cmds[j].is_last = (shell->parsed_input[i] == NULL);
		j++;
	}
	*cmd_count = j;
	return (cmds);
}

void	apply_redirections(char **cmd_args)
{
	char	*output_file;
	char	*input_file;
	int		fd;

	output_file = get_output_file(cmd_args);
	input_file = get_input_file(cmd_args);
	if (output_file)
	{
		fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		remove_redirection_tokens(cmd_args, ">");
		remove_redirection_tokens(cmd_args, ">>");
	}
	if (input_file)
	{
		fd = open(input_file, O_RDONLY);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		remove_redirection_tokens(cmd_args, "<");
	}
}

static void	setup_child_io(t_pipeline *cmd, int prev_pipe_in, int pipes[2])
{
	if (prev_pipe_in != 0)
		dup2(prev_pipe_in, STDIN_FILENO);
	if (!cmd->is_last && !get_output_file(cmd->cmd_args))
		dup2(pipes[1], STDOUT_FILENO);
	else
		apply_redirections(cmd->cmd_args);
	close(pipes[0]);
	if (!cmd->is_last)
		close(pipes[1]);
}

void	handle_child_process(t_minishell *shell, t_pipeline *cmd,
				int prev_pipe_in, int pipes[2])
{
	setup_child_io(cmd, prev_pipe_in, pipes);
	shell->parsed_input = cmd->cmd_args;
	if (is_builtin(cmd->cmd_args[0]))
		execute_command(shell);
	else
		execute_external_command(shell);
	exit(shell->exit_status);
}

void	handle_parent_process(int i, int cmd_count,
				int pipes[2], int *prev_pipe_in)
{
	if (i > 0)
		close(*prev_pipe_in);
	if (i < cmd_count - 1)
	{
		*prev_pipe_in = pipes[0];
		close(pipes[1]);
	}
}
