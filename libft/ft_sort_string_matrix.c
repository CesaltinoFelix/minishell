/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:52:24 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/27 12:42:49 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_string_matrix(char **matrix)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = -1;
	tmp = NULL;
	while (matrix[++len])
		;
	while (i < len - 1)
	{
		if (ft_strcmp(matrix[i], matrix[i + 1]) > 0)
		{
			tmp = matrix[i];
			matrix[i] = matrix[i + 1];
			matrix[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
