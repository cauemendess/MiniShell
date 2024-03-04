/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:46:31 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:08:26 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *find, size_t slen)
{
	size_t	i;
	size_t	len_find;

	i = 0;
	len_find = ft_strlen(find);
	if (*find == '\0')
		return ((char *)big);
	while (big[i] != '\0' && len_find <= slen)
	{
		if (ft_memcmp(&big[i], find, len_find) == 0)
		{
			return ((char *)&big[i]);
		}
		i++;
		slen--;
	}
	return (NULL);
}
