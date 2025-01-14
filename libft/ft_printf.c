/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:38:44 by pcapalan          #+#    #+#             */
/*   Updated: 2024/05/25 18:22:18 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(va_list args, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_printchar((char)va_arg(args, int));
	else if (c == 's')
		len += ft_print_string(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		ft_print_int((int)va_arg(args, int), &len);
	else if (c == 'u')
		ft_print_unsigned_int(va_arg(args, unsigned int), &len);
	else if (c == 'x' || c == 'X')
		ft_print_hex(va_arg(args, unsigned int), c, &len);
	else if (c == 'p')
		ft_print_pointer(va_arg(args, unsigned long), &len);
	else if (c == '%')
		len += ft_printchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_format(args, str[i + 1]);
			i++;
		}
		else
			len += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (len);
}
