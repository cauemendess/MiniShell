/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:08:54 by csilva-m          #+#    #+#             */
/*   Updated: 2023/09/26 11:31:24 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putsig(long int nb, char *base, char specifier)
{
	int	len;

	len = 0;
	if ((specifier == '+') && nb >= 0)
		len += ft_putchar('+');
	if ((specifier == ' ') && nb >= 0)
		len += ft_putchar(' ');
	len += ft_putnbr_base(nb, base);
	return (len);
}
