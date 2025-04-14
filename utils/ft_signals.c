/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:48:46 by pcapalan          #+#    #+#             */
/*   Updated: 2025/04/14 16:04:59 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_status = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	initialize_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int wait_for_signal(int pid)
{
	int	sig;
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		exit_status = 128 + sig;
		if (sig == SIGINT)
			write(1, "\n", 1);
	}
	signal(SIGINT, sigint_handler);
	return (exit_status);
}