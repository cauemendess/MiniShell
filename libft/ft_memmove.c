/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:27:37 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:06:50 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc;
	size_t				i;

	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	i = 0;
	if (!cdest && !csrc)
		return (NULL);
	if (cdest > csrc)
	{
		while (++i <= n)
			cdest[n - i] = csrc[n - i];
	}
	else
	{
		while (n > 0)
		{
			(*(cdest++) = *(csrc++));
			n--;
		}
	}
	return (dest);
}
