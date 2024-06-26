/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:24:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/23 17:28:41 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

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
