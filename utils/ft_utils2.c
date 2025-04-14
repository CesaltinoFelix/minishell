/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:08 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/14 15:29:44 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_append_mode(char **cmd_args)
{
    int i = 0;

    while (cmd_args[i] != NULL)
    {
        if (ft_strcmp(cmd_args[i], ">>") == 0) {
			return (O_WRONLY | O_CREAT | O_APPEND);
        }
        i++;
    }
	return (O_WRONLY | O_CREAT | O_TRUNC);
}