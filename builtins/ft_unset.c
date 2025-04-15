/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:03:06 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 17:11:43 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_env_var_unset(char *var_name, t_minishell *shell)
{
	int	i;

	i = 1;
	while (shell->parsed_input[i])
	{
		shell->env_var.key = shell->parsed_input[i];
		if (is_env_var_match(var_name, shell->env_var.key,
				ft_strlen(shell->env_var.key)))
			return (1);
		i++;
	}
	return (0);
}

static int	count_remaining_env_vars(t_minishell *shell)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (shell->env_variables[i])
	{
		if (!is_env_var_unset(shell->env_variables[i], shell))
			count++;
		i++;
	}
	return (count);
}

static int	allocate_new_env(t_minishell *shell, char ***new_env)
{
	int	valid_count;

	valid_count = count_remaining_env_vars(shell);
	*new_env = malloc(sizeof(char *) * (valid_count + 1));
	return (*new_env == NULL);
}

int	handle_unset_command(t_minishell *shell)
{
	int		i;
	int		j;
	char	**new_envarion;

	i = -1;
	j = -1;
	if (validate_unset_option(shell->parsed_input) || allocate_new_env(shell,
			&new_envarion))
		return (2);
	while (shell->env_variables[++i])
	{
		if (!is_env_var_unset(shell->env_variables[i], shell))
		{
			new_envarion[++j] = ft_strdup(shell->env_variables[i]);
			if (!new_envarion[j])
			{
				ft_free_matrix(new_envarion);
				return (2);
			}
		}
	}
	new_envarion[++j] = NULL;
	ft_free_matrix(shell->env_variables);
	shell->env_variables = new_envarion;
	return (0);
}
