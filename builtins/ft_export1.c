/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+        */
/*   Created: 2025/03/20 13:02:58 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:11:20 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_or_add_env_var(t_minishell *shell)
{
	char	*new_var;

	shell->env_var.equal_sign = ft_strchr(shell->env_var.key, '=');
	if (shell->env_var.equal_sign)
		shell->env_var.key_len = shell->env_var.equal_sign - shell->env_var.key;
	else
		shell->env_var.key_len = ft_strlen(shell->env_var.key);
	new_var = create_env_var_string(shell);
	if (!find_and_update_env_var(shell, new_var))
		add_env_var_to_array(shell, new_var);
}

int	handle_export_command(t_minishell *shell)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!shell->parsed_input[1])
		return (print_sorted_env_vars(shell), flag);
	while (shell->parsed_input[i])
	{
		if (is_valid_env_var_name(shell->parsed_input[i]))
		{
			extract_env_key_value(shell, shell->parsed_input[i]);
			update_or_add_env_var(shell);
			free(shell->env_var.key);
			free(shell->env_var.value);
		}
		else
		{
			print_invalid_identifier_error(shell->parsed_input[i]);
			flag = 1;
		}
		i++;
	}
	return (flag);
}
