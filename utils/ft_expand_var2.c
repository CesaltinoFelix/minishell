/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:01:34 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/25 16:06:09 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_updated_input(size_t updated_len)
{
	char	*updated_input;

	updated_input = malloc(updated_len + 1);
	if (!updated_input)
		return (NULL);
	return (updated_input);
}

void	remove_env_variable_from_input(t_minishell *shell)
{
	size_t	updated_len;
	char	*updated_input;
	size_t	chars_before_var;

	updated_len = ft_strlen(shell->input)
		- (shell->var_exp.end - shell->var_exp.start);
	updated_input = allocate_updated_input(updated_len);
	if (!updated_input)
		return ;
	chars_before_var = shell->var_exp.start - shell->input;
	ft_memcpy(updated_input, shell->input, chars_before_var);
	ft_strcpy(updated_input + chars_before_var, shell->var_exp.end);
	free(shell->input);
	shell->input = updated_input;
}

void	copy_replacement_to_input(t_minishell *shell, char *updated_input,
	size_t chars_before_var, size_t replacement_len)
{
	ft_memcpy(updated_input, shell->input, chars_before_var);
	ft_strcpy(updated_input + chars_before_var, shell->var_exp.value);
	ft_strcpy(updated_input + chars_before_var + replacement_len,
		shell->var_exp.end);
}

void	replace_env_variable_in_input(t_minishell *shell)
{
	char	*updated_input;
	size_t	chars_before_var;
	size_t	replacement_len;
	size_t	updated_len;

	chars_before_var = shell->var_exp.start - shell->input;
	replacement_len = ft_strlen(shell->var_exp.value);
	updated_len = ft_strlen(shell->input)
		- (shell->var_exp.end - shell->var_exp.start) + replacement_len;
	updated_input = allocate_updated_input(updated_len);
	if (!updated_input)
		return ;
	copy_replacement_to_input(shell, updated_input,
		chars_before_var, replacement_len);
	free(shell->input);
	shell->input = updated_input;
}

void	expand_single_env_variable(t_minishell *shell, char **current)
{
	if (count_backslashes_before(shell->input, shell->var_exp.start) % 2 == 1)
	{
		*current = shell->var_exp.start + 1;
		return ;
	}
	shell->var_exp.end = shell->var_exp.start + 1;
	if (*(shell->var_exp.end) == '?')
	{
		shell->display_exit_status = 1;
		shell->var_exp.end++;
	}
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
