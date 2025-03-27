/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/27 12:23:23 by cefelix          ###   ########.fr       */
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
