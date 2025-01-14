/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:46:21 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/21 02:01:51 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*ptr_s1;
	char	*ptr_s2;
	size_t	i;

	i = 0;
	ptr_s1 = (char *)s1;
	ptr_s2 = (char *)s2;
	while (i < n)
	{
		if (ptr_s1[i] != ptr_s2[i])
			return ((unsigned char)ptr_s1[i] - (unsigned char)ptr_s2[i]);
		i++;
	}
	return (0);
}
