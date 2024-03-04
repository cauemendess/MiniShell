/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:02:36 by csilva-m          #+#    #+#             */
/*   Updated: 2023/09/26 11:31:08 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(long int nb, char *base, char specifier)
{
	int	len;

	len = 0;
	if (nb != 0)
	{
		if ((specifier == '#') && (base[15] == 'F'))
			len += ft_putstr("0X");
		else if ((specifier == '#') && (base[15] == 'f'))
			len += ft_putstr("0x");
	}
	len += ft_putnbr_base(nb, base);
	return (len);
}
