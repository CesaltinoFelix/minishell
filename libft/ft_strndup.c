/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eymarplayboy7 <eymarplayboy7@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:52:24 by pcapalan          #+#    #+#             */
/*   Updated: 2025/02/26 15:15:01 by eymarplaybo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *str, size_t len)
{
    char *ptr = malloc(len + 1);
    if (!ptr)
        return (NULL);
    ft_strlcpy(ptr, str, len + 1);
    return (ptr);
}
