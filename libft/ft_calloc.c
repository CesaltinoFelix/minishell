/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:41:00 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/21 21:59:04 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_size;
	void	*ptr;

	if (count == 0 || size == 0)
		t_size = 0;
	else
	{
		t_size = count * size;
		if (t_size / size != count)
			return (NULL);
	}
	ptr = malloc(t_size);
	if (ptr == NULL)
		return (NULL);
	else
		ft_bzero(ptr, t_size);
	return (ptr);
}
