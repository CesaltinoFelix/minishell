/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:51 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:09:12 by cefelix          ###   ########.fr       */
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
