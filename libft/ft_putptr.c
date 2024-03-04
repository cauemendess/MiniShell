/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:27 by csilva-m          #+#    #+#             */
/*   Updated: 2023/09/26 11:31:20 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long nb, char *base)
{
	unsigned long	base_len;
	int				len;

	len = 0;
	base_len = ft_strlen(base);
	if (nb == 0)
		return (ft_putstr("(nil)"));
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= base_len)
		len += ft_putptr(nb / base_len, base);
	else
		len += ft_putstr("0x");
	len += ft_putchar(base[nb % base_len]);
	return (len);
}
