/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:50:02 by pcapalan          #+#    #+#             */
/*   Updated: 2025/01/11 20:34:42 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_nb(const char *s, char c)
{
	size_t	word_nb;

	word_nb = 0;
	while (*s)
	{
		if (*s != c)
		{
			++word_nb;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (word_nb);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**new_str;

	if (!s)
		return (0);
	i = 0;
	new_str = malloc(sizeof(char *) * (ft_word_nb(s, c) + 1));
	if (!new_str)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			new_str[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	new_str[i] = 0;
	return (new_str);
}