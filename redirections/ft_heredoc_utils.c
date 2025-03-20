/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:37 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:23:11 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int g_heredoc_interrupted;

void heredoc_signal_handler(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    exit(130);
}

void setup_heredoc_signals()
{
    struct sigaction sa_int;

    sa_int.sa_handler = heredoc_signal_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
}

void ignore_sigint()
{
    struct sigaction sa_ignore;

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);
}

void restore_sigint()
{
    struct sigaction sa_default;

    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sigaction(SIGINT, &sa_default, NULL);
}

int wait_for_heredoc(t_minishell *shell, int pid, char *file)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status) == 130)
        {
            shell->exit_status = 130;
            unlink(file);
            return (-1);
        }
    }
    else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        unlink(file);
        return (-1);
    }
    return (0);
}
