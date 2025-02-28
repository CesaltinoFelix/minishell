/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:51:42 by pcapalan          #+#    #+#             */
/*   Updated: 2025/02/28 16:58:57 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_iter
{
	size_t	i;
	size_t	size;
}	t_iter;

typedef struct s_read
{
	size_t	bytes;
	size_t	pos;
}	t_read;

char	*get_next_line(int fd);
size_t	str_len(const char *s);
void	init_iter(t_iter *it);
char	*resize_buf(char *line, size_t *cap);
size_t	read_buf(int fd, char *buf, size_t *bytes, size_t *pos);

#endif
