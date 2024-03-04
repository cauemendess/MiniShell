/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:01:04 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:06:22 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*arr;

	i = 0;
	arr = s;
	while (i < n)
	{
		if (arr[i] == (unsigned char)c)
		{
			return ((void *)&arr[i]);
		}
		i++;
	}
	return (NULL);
}
