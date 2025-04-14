/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/14 15:27:52 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipeline(t_minishell *shell, t_pipeline *cmds, int cmd_count)
{
	int		pipes[2];
	int		prev_pipe_in;
	pid_t	pid;
	int		i;

	prev_pipe_in = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (i < cmd_count - 1)
			pipe(pipes);
		pid = fork();
		if (pid == 0)
			handle_child_process(shell, &cmds[i], prev_pipe_in, pipes);
		else
			handle_parent_process(i, cmd_count, pipes, &prev_pipe_in);
		i++;
	}
	while (waitpid(0, &shell->exit_status, 0) > 0)
		;
	shell->exit_status = WEXITSTATUS(shell->exit_status);
}

void	apply_redirections(char **cmd_args)
{
	char	*output_file;
	char	*input_file;
	int		fd;
	int flags;

	flags = is_append_mode(cmd_args);
	output_file = get_output_file(cmd_args);
	input_file = get_input_file(cmd_args);
	if (output_file)
	{
		fd = open(output_file, flags, 0644);
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
	char	**parsed_input;

	parsed_input = shell->parsed_input;
	setup_child_io(cmd, prev_pipe_in, pipes);
	shell->parsed_input = cmd->cmd_args;
	if (is_builtin(cmd->cmd_args[0]))
		execute_command(shell);
	else
		execute_external_command(shell);
	shell->parsed_input = parsed_input;
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
