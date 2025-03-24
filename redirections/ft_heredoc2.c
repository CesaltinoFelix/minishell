/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/24 12:56:36 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	create_temp_file(char *file)
{
	int		fd;
	char	*pid_str;
	char	*prefix;

	prefix = "/tmp/minishell_heredoc_";
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (-1);
	ft_memcpy(file, prefix, ft_strlen(prefix) + 1);
	ft_strlcat(file, pid_str, 128);
	free(pid_str);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("error opening file");
	return (fd);
}
