/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:21:46 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 ||
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 ||
		ft_strcmp(cmd, "exit") == 0);
}

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
		cmds[j].cmd_args = &shell->parsed_input[i];
		cmds[j].fd_in = STDIN_FILENO;
		cmds[j].fd_out = STDOUT_FILENO;
		while (shell->parsed_input[i] && ft_strcmp(shell->parsed_input[i], "|") != 0)
			i++;
		if (shell->parsed_input[i] && ft_strcmp(shell->parsed_input[i], "|") == 0)
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

static char	*get_output_file(char **cmd_args)
{
	int	i;

i = 0;
	while (cmd_args[i])
	{
		if (ft_strcmp(cmd_args[i], ">") == 0 || ft_strcmp(cmd_args[i], ">>") == 0)
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

static char	*get_input_file(char **cmd_args)
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

static void	remove_redirection_tokens(char **cmd_args, char *token)
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

void	apply_redirections(char **cmd_args)
{
	char	*output_file;
	char	*input_file;

output_file = get_output_file(cmd_args);
	input_file = get_input_file(cmd_args);
	if (output_file)
	{
		int	fd;

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
		int	fd;

fd = open(input_file, O_RDONLY);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		remove_redirection_tokens(cmd_args, "<");
	}
}

void	execute_pipeline(t_minishell *shell, t_pipeline *cmds, int cmd_count)
{
	int		pipes[2];
	int		prev_pipe_in;
	pid_t	pid;

prev_pipe_in = 0;
	for (int i = 0; i < cmd_count; i++)
	{
		if (i < cmd_count - 1)
			pipe(pipes);
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
				dup2(prev_pipe_in, STDIN_FILENO);
			if (i < cmd_count - 1 && !get_output_file(cmds[i].cmd_args))
				dup2(pipes[1], STDOUT_FILENO);
			else
				apply_redirections(cmds[i].cmd_args);
			close(pipes[0]);
			if (i < cmd_count - 1)
				close(pipes[1]);
			shell->parsed_input = cmds[i].cmd_args;
			if (is_builtin(cmds[i].cmd_args[0]))
				execute_command(shell);
			else
				execute_external_command(shell);
			exit(shell->exit_status);
		}
		else
		{
			if (i > 0)
				close(prev_pipe_in);
			if (i < cmd_count - 1)
			{
				prev_pipe_in = pipes[0];
				close(pipes[1]);
			}
		}
	}
	while (waitpid(0, &shell->exit_status, 0) > 0)
		;
	shell->exit_status = WEXITSTATUS(shell->exit_status);
}