/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:22:35 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/25 18:20:50 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_hex_lower(unsigned long long nb, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb > 15)
		ft_print_hex_lower(nb / 16, len);
	ft_printchar(base[nb % 16]);
	(*len)++;
}

void	ft_print_pointer(unsigned long long p, int *len)
{
	if (p == 0)
	{
		ft_print_string("(nil)");
		(*len) += 5;
		return ;
	}
	ft_print_string("0x");
	(*len) += 2;
	ft_print_hex_lower(p, len);
}

void	ft_print_hex(unsigned int nb, char c, int *len)
{
	char	*base;
	char	*base2;

	base = "0123456789abcdef";
	base2 = "0123456789ABCDEF";
	if (nb > 15)
		ft_print_hex(nb / 16, c, len);
	if (c == 'X')
		ft_printchar(base2[nb % 16]);
	else
		ft_printchar(base[nb % 16]);
	(*len)++;
}
