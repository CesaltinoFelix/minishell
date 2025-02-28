/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:56:47 by pcapalan          #+#    #+#             */
/*   Updated: 2025/02/28 16:58:06 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	static t_read	rd = {0, 0};
	t_iter		it;

	line = NULL;
	init_iter(&it);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (rd.pos >= rd.bytes && read_buf(fd, buf, &rd.bytes, &rd.pos) <= 0)
			break;
		if (it.i >= it.size && !(line = resize_buf(line, &it.size)))
			return (NULL);
		line[it.i++] = buf[rd.pos++];
		if (line[it.i - 1] == '\n')
			break;
	}
	if (it.i == 0)
		return (free(line), NULL);
	line[it.i] = '\0';
	return (line);
}
