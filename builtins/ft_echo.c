/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:47 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 12:55:24 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_echo_options(t_minishell *shell, \
int *print_newline, int *arg_index)
{
	int	char_index;

	while (shell->parsed_input[*arg_index] && \
	shell->parsed_input[*arg_index][0] == '-'
		&& shell->parsed_input[*arg_index][1] == 'n')
	{
		char_index = 2;
		while (shell->parsed_input[*arg_index][char_index] == 'n')
			char_index++;
		if (shell->parsed_input[*arg_index][char_index] == '\0')
			*print_newline = 0;
		else
			break ;
		(*arg_index)++;
	}
}

int	handle_echo_command(t_minishell *shell)
{
	int	arg_index;
	int	print_newline;

	arg_index = 1;
	print_newline = 1;
	handle_echo_options(shell, &print_newline, &arg_index);
	while (shell->parsed_input[arg_index])
	{
		printf("%s", shell->parsed_input[arg_index]);
		if (shell->parsed_input[arg_index + 1])
			printf(" ");
		arg_index++;
	}
	if (print_newline)
		printf("\n");
	return (0);
}
