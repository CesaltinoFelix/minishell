/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:21:02 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/25 18:28:23 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_string(char *str)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

void	ft_print_int(int nb, int *len)
{
	if (nb == -2147483648)
	{
		ft_printchar('-');
		ft_printchar('2');
		*len += 2;
		ft_print_int(147483648, len);
	}
	else if (nb < 0)
	{
		ft_printchar('-');
		(*len)++;
		ft_print_int(-nb, len);
	}
	else if (nb > 9)
	{
		ft_print_int(nb / 10, len);
		ft_printchar(nb % 10 + '0');
		(*len)++;
	}
	else
	{
		ft_printchar(nb + '0');
		(*len)++;
	}
}

void	ft_print_unsigned_int(unsigned int nb, int *len)
{
	if (nb > 9)
	{
		ft_print_unsigned_int(nb / 10, len);
		ft_printchar(nb % 10 + '0');
		(*len)++;
	}
	else
	{
		ft_printchar(nb + '0');
		(*len)++;
	}
}
