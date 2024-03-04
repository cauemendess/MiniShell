/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:41:14 by csilva-m          #+#    #+#             */
/*   Updated: 2023/09/26 11:31:03 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_validate(va_list args, const char format, char specifier)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format == 'i' || format == 'd')
		count += ft_putsig(va_arg(args, int), DEC_BASE, specifier);
	else if (format == 'u')
		count += ft_putnbr_base(va_arg(args, unsigned int), DEC_BASE);
	else if (format == 'p')
		count += ft_putptr(va_arg(args, unsigned long), HEX_BASE);
	else if (format == 'x')
		count += ft_puthex(va_arg(args, unsigned int), HEX_BASE, specifier);
	else if (format == 'X')
		count += ft_puthex(va_arg(args, unsigned int), HEX_BASE_UPPER,
				specifier);
	else if (format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	ret = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			while (format[i] == '#' || format[i] == '+' || format[i] == ' ')
				i++;
			ret += ft_validate(args, format[i], format[i - 1]);
		}
		else
			ret += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (ret);
}
