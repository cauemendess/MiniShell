/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:41:50 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/06 20:12:15 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		index;
	char	*new_string;

	index = 0;
	if (src == NULL)
		return (NULL);
	new_string = malloc(ft_strlen(src) + 1);
	if (!new_string)
		return (0);
	while (src[index] != '\0')
	{
		new_string[index] = src[index];
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
}
