/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:16 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/25 16:17:15 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[], char *env[])
{
	extern int	g_status;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	initialize_signal_handlers();
	init_shell(&shell, env);
	run_shell(&shell);
	if (g_status == 130)
		shell.exit_status = g_status;
	return (shell.exit_status);
}
