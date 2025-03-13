/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:48:46 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/12 17:48:49 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int g_status = 0;
int g_heredoc_interrupted = 0; 

 void sigint_handler(int sig)
{
    (void)sig;
    g_status = 130;
    g_heredoc_interrupted = 1;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
}

void initialize_signal_handlers()
{
    struct sigaction sa_int;

    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction(SIGINT) failed");
        exit(1);
    }
}
