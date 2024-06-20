/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:33:28 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/20 18:30:38 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		dest_i;
	int		i;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	dest_i = 0;
	i = 0;
	while (s1 && s1[i])
	{
		dest[dest_i] = s1[i];
		i++;
		dest_i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		dest[dest_i] = s2[i];
		i++;
		dest_i++;
	}
	dest[dest_i] = '\0';
	return (dest);
}
