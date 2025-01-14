/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:53:12 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/21 23:45:52 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;

	if (start >= ft_strlen(s))
	{
		new_str = (char *)malloc(sizeof(char));
		if (!new_str)
			return (NULL);
		*new_str = '\0';
	}
	else
	{
		if (ft_strlen(s) - start < len)
			len = ft_strlen(s) - start;
		new_str = (char *)malloc((sizeof(char) * len) + 1);
		if (!new_str)
			return (NULL);
		ft_strlcpy(new_str, (char *)(s + start), len + 1);
	}
	return (new_str);
}
