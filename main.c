/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:16 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/10 14:32:46 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *env[])
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	initialize_signal_handlers();
	init_shell(&shell, env);
	run_shell(&shell);
	return (shell.exit_status);
}
