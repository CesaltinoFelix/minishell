/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:54 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 17:11:27 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify_range(t_minishell *shell, char **ptr, long long int *result,
		int signal)
{
	int	digit;

	while (ft_isdigit(**ptr))
	{
		digit = **ptr - '0';
		if ((signal == 1 && *result > (LLONG_MAX - digit) / 10) || (signal == -1
				&& *result > (-(LLONG_MIN + digit)) / 10))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				shell->parsed_input[1]);
			shell->exit_status = 2;
			return (-1);
		}
		*result = *result * 10 + digit;
		(*ptr)++;
	}
	if (**ptr != '\0')
	{
		printf("minishell: exit: %s: numeric argument required\n",
			shell->parsed_input[1]);
		shell->exit_status = 2;
		return (-1);
	}
	return (0);
}

static int	ft_atoi2(t_minishell *shell, char *ptr)
{
	int				signal;
	long long int	result;

	signal = 1;
	result = 0;
	while (*ptr == 32 || (*ptr >= 9 && *ptr <= 13))
		ptr++;
	if (*ptr == 43 || *ptr == 45)
	{
		if (*ptr == 45)
			signal = -1;
		ptr++;
	}
	if (verify_range(shell, &ptr, &result, signal) != 0)
		return (-1);
	shell->exit_status = (int)((result * signal) & 255);
	return (0);
}

void	handle_exit_command(t_minishell *shell)
{
	printf("exit\n");
	if (shell->parsed_input[1])
		ft_atoi2(shell, shell->parsed_input[1]);
	check_to_free(shell);
	exit(shell->exit_status);
}
