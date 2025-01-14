/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:51:34 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/20 13:02:15 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i_s1;
	int		j_s2;
	char	*new_str;

	i_s1 = 0;
	j_s2 = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[i_s1] != '\0')
	{
		new_str[i_s1] = s1[i_s1];
		i_s1++;
	}
	while (s2[j_s2] != '\0')
	{
		new_str[i_s1 + j_s2] = s2[j_s2];
		j_s2++;
	}
	new_str[i_s1 + j_s2] = '\0';
	return (new_str);
}
