/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:01:44 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 23:14:42 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_error(char *str, char *write_error)
{
	write(2, str, ft_strlen(str));
	ft_putendl_fd(write_error, 2);
}

void	print_invalid_identifier_error(const char *arg)
{
	printf("minishell: export: `%s`: not a valid identifier\n", arg);
}

int	validate_unset_option(char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		printf("%s: %s: invalid option\n", args[0], args[1]);
		return (2);
	}
	return (0);
}
