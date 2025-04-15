/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:51 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 12:55:34 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_env_command(t_minishell *shell)
{
	int	i;

	i = 0;
	if (shell->parsed_input[1] != NULL)
	{
		printf("No such file or directory\n");
		return (127);
	}
	while (shell->env_variables[i])
	{
		if (ft_strchr(shell->env_variables[i], '='))
			printf("%s\n", shell->env_variables[i]);
		i++;
	}
	return (0);
}
