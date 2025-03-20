/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:03:02 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:12:51 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_pwd_command(t_minishell *shell)
{
    char current_directory[255];

    if (shell->parsed_input[1])  
    {
        if (!ft_isalpha(shell->parsed_input[1][0]))
        {
            printf("%s: %s: invalid option\n", shell->parsed_input[0], shell->parsed_input[1]);
            return (2);
        }
    }
    if (getcwd(current_directory, sizeof(current_directory)))
        printf("%s\n", current_directory);
    return (0);
}
