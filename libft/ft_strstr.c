/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:12:41 by csilva-m          #+#    #+#             */
/*   Updated: 2024/03/07 16:12:47 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *find)
{
	size_t	i;
	size_t	len_find;

	i = 0;
	len_find = ft_strlen(find);
	if (*find == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		if (ft_memcmp(&big[i], find, len_find) == 0)
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
