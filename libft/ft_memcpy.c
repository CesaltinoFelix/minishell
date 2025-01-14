/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:48:47 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/20 13:43:13 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest_n;
	char	*src_n;

	i = 0;
	dest_n = (char *)dest;
	src_n = (char *)src;
	while (i < n)
	{
		dest_n[i] = src_n[i];
		i++;
	}
	return (dest);
}
