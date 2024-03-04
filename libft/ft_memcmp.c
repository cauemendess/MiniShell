/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:35:17 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:06:26 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*src1;
	const unsigned char	*src2;
	size_t				i;

	i = 0;
	src1 = s1;
	src2 = s2;
	while (i < n)
	{
		if (src1[i] < src2[i])
			return (-1);
		else if (src1[i] > src2[i])
			return (1);
		i++;
	}
	return (0);
}
