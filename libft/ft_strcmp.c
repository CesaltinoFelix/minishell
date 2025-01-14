/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: playboy7xb <playboy7xb@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:46:21 by pcapalan          #+#    #+#             */
/*   Updated: 2025/01/14 20:36:22 by playboy7xb       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
        unsigned int i;

        i = 0;
        while (s1[i] && s2[i] && s1[i] == s2[i])
                i++;
        return ((unsigned int)s1[i] - (unsigned)s2[i]);
}