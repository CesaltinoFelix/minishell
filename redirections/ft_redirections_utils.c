/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:41:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/25 16:41:32 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_output_redirection(char *str)
{
	return (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"));
}

void	remove_redirection(t_minishell *shell, int i)
{
	int	j;

	j = i;
	free(shell->parsed_input[j]);
	free(shell->parsed_input[j + 1]);
	while (shell->parsed_input[j + 2])
	{
		shell->parsed_input[j] = shell->parsed_input[j + 2];
		j++;
	}
	shell->parsed_input[j] = NULL;
	shell->parsed_input[j + 1] = NULL;
}

void	ft_restore_stdio(t_minishell *shell)
{
	if (!shell)
		return ;
	if (shell->stdout_backup != -1)
	{
		dup2(shell->stdout_backup, STDOUT_FILENO);
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
	if (shell->stdin_backup != -1)
	{
		dup2(shell->stdin_backup, STDIN_FILENO);
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
}
