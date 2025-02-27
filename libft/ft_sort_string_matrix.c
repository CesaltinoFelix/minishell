/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_string_matrix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eymarplayboy7 <eymarplayboy7@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:52:24 by pcapalan          #+#    #+#             */
/*   Updated: 2025/02/26 15:15:16 by eymarplaybo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_sort_string_matrix(char **matrix)
{
    int i;
    int len;
    char *tmp;
    
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