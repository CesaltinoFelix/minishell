/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:21 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/27 12:14:38 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	handle_redirection_error(t_minishell *shell, int i)
{
	if (!ft_strcmp(shell->parsed_input[i + 1], ">")
		|| !ft_strcmp(shell->parsed_input[i + 1], "<")
		|| !ft_strcmp(shell->parsed_input[i + 1], ">>")
		|| !ft_strcmp(shell->parsed_input[i + 1], "<<"))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			shell->parsed_input[i + 1]);
		return (-1);
	}
	return (0);
}

int	set_output_flags(char *redir_type)
{
	if (!ft_strcmp(redir_type, ">"))
		return (O_WRONLY | O_CREAT | O_TRUNC);
	return (O_WRONLY | O_CREAT | O_APPEND);
}
