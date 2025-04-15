/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 21:14:29 by cefelix          ###   ########.fr       */
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
		if (i < cmd_count - 1 && pipe(pipes) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
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

static void	remove_all_redir_tokens(char **cmd_args)
{
	remove_redirection_tokens(cmd_args, ">");
	remove_redirection_tokens(cmd_args, ">>");
	remove_redirection_tokens(cmd_args, "<");
}

static void	setup_child_input(char *input_file, int prev_pipe_in)
{
	int	fd;

	if (input_file)
	{
		fd = open(input_file, O_RDONLY);
		if (fd == -1)
		{
			perror(input_file);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (prev_pipe_in != 0)
		dup2(prev_pipe_in, STDIN_FILENO);
}

static void	setup_child_output(\
	char *output_file, char **cmd_args, int *pipes, int is_last)
{
	int	fd;

	if (output_file)
	{
		fd = open(output_file, is_append_mode(cmd_args), 0644);
		if (fd == -1)
		{
			perror(output_file);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (!is_last)
		dup2(pipes[1], STDOUT_FILENO);
}

void	setup_child_io(t_pipeline *cmd, int prev_pipe_in, int pipes[2])
{
	char	*output_file;
	char	*input_file;

	output_file = get_output_file(cmd->cmd_args);
	input_file = get_input_file(cmd->cmd_args);
	setup_child_input(input_file, prev_pipe_in);
	setup_child_output(output_file, cmd->cmd_args, pipes, cmd->is_last);
	close(pipes[0]);
	if (!cmd->is_last)
		close(pipes[1]);
	remove_all_redir_tokens(cmd->cmd_args);
}
