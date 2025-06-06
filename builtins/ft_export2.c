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

void	extract_env_key_value(t_minishell *shell, const char *arg)
{
	size_t	equal_sign_pos;

	equal_sign_pos = 0;
	while (arg[equal_sign_pos] && arg[equal_sign_pos] != '=')
		equal_sign_pos++;
	shell->env_var.key = ft_strndup(arg, equal_sign_pos);
	if (arg[equal_sign_pos] == '=')
		shell->env_var.value = ft_strdup(arg + equal_sign_pos + 1);
	else
		shell->env_var.value = NULL;
}

char	*create_env_var_string(t_minishell *shell)
{
	int		total_length;
	char	*var_name;

	total_length = ft_strlen(shell->env_var.key) + 2;
	if (shell->env_var.value)
		total_length += ft_strlen(shell->env_var.value);
	var_name = malloc(sizeof(char) * total_length);
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, shell->env_var.key, total_length);
	if (shell->env_var.value)
	{
		ft_strlcat(var_name, "=", total_length);
		ft_strlcat(var_name, shell->env_var.value, total_length);
	}
	return (var_name);
}

void	add_env_var_to_array(t_minishell *shell, char *new_var)
{
	int		i;
	char	**new_envarion;

	i = 0;
	while (shell->env_variables[i])
		i++;
	new_envarion = malloc(sizeof(char *) * (i + 2));
	if (!new_envarion)
		return ;
	i = -1;
	while (shell->env_variables[++i])
		new_envarion[i] = ft_strdup(shell->env_variables[i]);
	new_envarion[i] = ft_strdup(new_var);
	new_envarion[i + 1] = NULL;
	free(new_var);
	ft_free_matrix(shell->env_variables);
	shell->env_variables = new_envarion;
}

int	find_and_update_env_var(t_minishell *shell, char *new_var)
{
	int	i;

	i = -1;
	while (shell->env_variables[++i])
	{
		if (is_env_var_match(shell->env_variables[i], shell->env_var.key,
				shell->env_var.key_len))
		{
			if (shell->env_var.value)
			{
				free(shell->env_variables[i]);
				shell->env_variables[i] = ft_strdup(new_var);
			}
			free(new_var);
			return (1);
		}
	}
	return (0);
}
