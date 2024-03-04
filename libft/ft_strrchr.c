/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:21:20 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:08:29 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *p, int ch)
{
	int	i;

	i = ft_strlen(p);
	while (i >= 0)
	{
		if (p[i] == (unsigned char)ch)
			return ((char *)&p[i]);
		i--;
	}
	return (0);
}
