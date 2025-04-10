/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:05 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/10 19:11:14 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_exit_status(t_minishell *shell)
{
	extern int	g_status;
	
	if (g_status == 130)
		shell->exit_status = 130;
	else
	{
		g_status = shell->exit_status;
	}
}

void	run_shell(t_minishell *shell)
{
	extern int	g_status;
	char	*trimmed_input;

	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
		{
			printf("exit\n");
			break ;
		}
		trimmed_input = trim_whitespace(shell->input);
		free(shell->input);
		shell->input = trimmed_input;
		change_exit_status(shell);
		if (*shell->input)
		{
			add_history(shell->input);
			process_user_input(shell);
			g_status = shell->exit_status;
		}
		check_to_free(shell);
	}
	ft_free_matrix(shell->env_variables);
	check_to_free(shell);
}
