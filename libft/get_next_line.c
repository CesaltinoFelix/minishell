/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:56:47 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/27 12:48:18 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	process_buffer(char **line, t_iter *it, char *buf, t_read *rd)
{
	if (it->i >= it->size)
	{
		*line = resize_buf(*line, &it->size);
		if (!*line)
			return (0);
	}
	(*line)[it->i++] = buf[rd->pos++];
	if ((*line)[it->i - 1] == '\n')
		return (0);
	return (1);
}

static int	handle_buffer_refill(int fd, char *buf, t_read *rd)
{
	if (read_buf(fd, buf, &rd->bytes, &rd->pos) <= 0)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static t_read	rd = {0, 0};
	char			*line;
	t_iter			it;

	line = NULL;
	init_iter(&it);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (rd.pos >= rd.bytes && !handle_buffer_refill(fd, buf, &rd))
			break ;
		if (!process_buffer(&line, &it, buf, &rd))
			break ;
	}
	if (it.i == 0)
	{
		free(line);
		return (NULL);
	}
	line[it.i] = '\0';
	return (line);
}
