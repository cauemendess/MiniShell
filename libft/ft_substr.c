/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:24:38 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:08:36 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start) + 1;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, (s + start), len + 1);
	return (dest);
}
