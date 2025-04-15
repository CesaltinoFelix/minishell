/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:56:38 by pcapalan          #+#    #+#             */
/*   Updated: 2025/04/15 13:13:01 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../minishell.h"

extern int g_status;

void	heredoc_signal_handler(int sig)
{
    (void)sig;
    g_status = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0); 
    exit(130);
}

void	ignore_sigint()
{
    signal(SIGINT, SIG_IGN);
}


int	redirect_heredoc_input(t_minishell *shell, char *file)
{
	int	fd;

	if (shell->stdin_backup == -1)
		shell->stdin_backup = dup(STDIN_FILENO);
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("open");
		printf("error: could not open heredoc file\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("error: dup2 failed\n");
		return (close(fd), -1);
	}
	close(fd);
	unlink(file);
	return (0);
}

int	wait_for_heredoc(t_minishell *shell, int pid, char *file)
{
    int		status;
    int		exit_status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        exit_status = WEXITSTATUS(status);
        if (exit_status == 130)
        {
            shell->exit_status = 130;
            return (unlink(file), -1);
        }
    }
    return (0);
}
