/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manipulation_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:01:58 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/11 13:33:13 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cpy_env_variables(char *env[])
{
	int		i;
	int		len;
	char	**new_env;

	len = ft_matrix_len(env);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**duplicate_matrix_without_quotes(char **matrix, int size)
{
	char	**copy;
	int		i;
	int		len;

	i = 0;
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	while (matrix[i] && i < size)
	{
		len = unquoted_strlen(matrix[i]);
		copy[i] = malloc(sizeof(char) * (len + 1));
		if (!copy[i])
		{
			ft_free_matrix(copy);
			return (NULL);
		}
		copy_without_quotes(copy[i], matrix[i], len);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**tokenize_input(t_minishell *shell)
{
	char	**tokens;

	tokens = ft_split_quoted(shell->input, ' ');
	if (!tokens)
		return (NULL);
	shell->parsed_input = tokens;
	if (shell->parsed_input == NULL)
		return (NULL);
	return (shell->parsed_input);
}

char	*ft_getenv(t_minishell *shell, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (shell->env_variables[i] != NULL)
	{
		if (ft_strncmp(shell->env_variables[i], key, key_len) == 0
			&& shell->env_variables[i][key_len] == '=')
			return (&shell->env_variables[i][key_len + 1]);
		i++;
	}
	return (NULL);
}
