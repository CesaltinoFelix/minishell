/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: playboy7xb <playboy7xb@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:51:42 by pcapalan          #+#    #+#             */
/*   Updated: 2025/01/23 10:22:34 by playboy7xb       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strcat(char *dst, const char *src)
{
	size_t dst_len;
	size_t i;

	i = 0;
	dst_len = ft_strlen(dst);
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	
	return(ft_strlen(dst));
}
