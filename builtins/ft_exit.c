/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:54 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:09:43 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_numeric_argument(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	handle_exit_command(t_minishell *shell)
{
	long	numeric_exit_code;

	printf("exit\n");
	if (shell->parsed_input[1])
	{
		if (!is_valid_numeric_argument(shell->parsed_input[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", shell->parsed_input[1]);
			shell->exit_status = 2;
		}
		else if (shell->parsed_input[2])
		{
			printf("minishell: exit: too many arguments\n");
			shell->exit_status = 1;
			return;
		}
		else
		{
			numeric_exit_code = ft_atoi(shell->parsed_input[1]);
			shell->exit_status = (numeric_exit_code & 255);
		}
	}
	check_to_free(shell);
	exit(shell->exit_status);
}
