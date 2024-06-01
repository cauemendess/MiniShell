/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:41:14 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/01 13:42:19 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	size_t	i;
	int		length;

	if (string == NULL)
		return (-1);
	va_start(args, string);
	i = 0;
	length = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			length += ft_format_handler(args, string[i]);
		}
		else
			length += ft_putchar(string[i]);
		i++;
	}
	va_end(args);
	return (length);
}

int	ft_format_handler(va_list args, char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_putchar((char)va_arg(args, int));
	else if (format == 's')
		length += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		length += ft_putptr(va_arg(args, unsigned long), HEX_LW);
	else if (format == 'd' || format == 'i')
		length += ft_putnbr_base(va_arg(args, int), DEC);
	else if (format == 'u')
		length += ft_putnbr_base(va_arg(args, unsigned int), DEC);
	else if (format == 'x')
		length += ft_putnbr_base(va_arg(args, unsigned int), HEX_LW);
	else if (format == 'X')
		length += ft_putnbr_base(va_arg(args, unsigned int), HEX_UP);
	else if (format == '%')
		length += ft_putchar('%');
	return (length);
}