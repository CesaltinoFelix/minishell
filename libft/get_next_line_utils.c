/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:53:14 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/27 12:36:24 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_iter(t_iter *it)
{
	it->i = 0;
	it->size = 0;
}

size_t	read_buf(int fd, char *buf, size_t *bytes, size_t *pos)
{
	*bytes = read(fd, buf, BUFFER_SIZE);
	if (*bytes == (size_t)-1)
		return (0);
	*pos = 0;
	return (*bytes);
}

char	*resize_buf(char *line, size_t *size)
{
	size_t	i;
	size_t	new_size;
	char	*new_line;

	if (*size == 0)
		new_size = BUFFER_SIZE;
	else
		new_size = *size * 2;
	new_line = (char *)malloc(new_size);
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	*size = new_size;
	return (new_line);
}
