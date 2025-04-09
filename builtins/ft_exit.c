/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:54 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/08 14:04:02 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void verify_range(t_minishell *shell, long long int res)
{
	printf("%lld", res);
	if (res > LLONG_MAX || res < LLONG_MIN)
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		shell->parsed_input[1]);
		shell->exit_status = 2;
		return ;
	}
	shell->exit_status =  (res  & 255);
}

void	ft_atoi2(t_minishell *shell,char *ptr)
{
	int	signal;
	long long int	result;

	signal = 1;
	result = 0;
	while (*ptr == 32 || (*ptr >= 9 &&  *ptr <= 13))
		ptr++;
	if (*ptr == 43 || *ptr == 45)
	{
		if (*ptr == 45)
			signal = -1;
		ptr++;
	}
	while (ft_isdigit(*ptr))
		result = result * 10 + (*ptr++ - '0');
	if (*ptr != '\0')
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		shell->parsed_input[1]);
		shell->exit_status = 2;
		return;
	}
	verify_range(shell, result * signal);
}
// int	is_valid_numeric_argument(const char *str)
// {
// 	if (!str || !*str)
// 		return (0);
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	while (*str == ' ')
// 		str++;
// 	while (*str)
// 	{
// 		if (!ft_isdigit(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

void	handle_exit_command(t_minishell *shell)
{

	printf("exit\n");
	if (shell->parsed_input[1])
	{
		ft_atoi2(shell, shell->parsed_input[1]);
		if (shell->parsed_input[2])
		{
			printf("minishell: exit: too many arguments\n");
			shell->exit_status = 1;
			return ;
		}
	}
	check_to_free(shell);
	exit(shell->exit_status);
}
