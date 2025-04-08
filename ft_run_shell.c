/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:05 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/08 09:21:53 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_shell(t_minishell *shell)
{
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
		if (*shell->input)
		{
			add_history(shell->input);
			process_user_input(shell);
		}
		check_to_free(shell);
	}
	ft_free_matrix(shell->env_variables);
	check_to_free(shell);
}
