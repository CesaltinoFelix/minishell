/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:01:34 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/08 12:06:45 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env_variable(t_minishell *shell)
{
	size_t	var_name_len;

	if (shell->display_exit_status)
	{
		shell->var_exp.value = ft_itoa(shell->exit_status);
		replace_env_variable_in_input(shell);
		shell->display_exit_status = 0;
		free(shell->var_exp.value);
		return ;
	}
	var_name_len = shell->var_exp.end - (shell->var_exp.start + 1);
	shell->var_exp.name = ft_strndup(shell->var_exp.start + 1, var_name_len);
	if (!shell->var_exp.name)
		return ;
	shell->var_exp.value = ft_getenv(shell, shell->var_exp.name);
	free(shell->var_exp.name);
	shell->var_exp.name = NULL;
	if (!shell->var_exp.value)
		remove_env_variable_from_input(shell);
	else
		replace_env_variable_in_input(shell);
}

void	expand_single_env_variable(t_minishell *shell, char **current)
{
	if (ft_aux_expand_single_env(shell, current))
		return ;
	else
	{
		while (ft_isalnum(*(shell->var_exp.end))
			|| *(shell->var_exp.end) == '_')
			shell->var_exp.end++;
		if (shell->var_exp.end == shell->var_exp.start + 1)
		{
			*current = shell->var_exp.start + 1;
			return ;
		}
	}
	expand_env_variable(shell);
	*current = shell->input;
}

void	expand_all_env_variables(t_minishell *shell)
{
	char	*current;

	current = shell->input;
	shell->var_exp.start = ft_strchr(current, '$');
	while (shell->var_exp.start != NULL)
	{
		expand_single_env_variable(shell, &current);
		shell->var_exp.start = ft_strchr(current, '$');
	}
	remove_escaped_dollar_and_backslash(shell->input);
}
