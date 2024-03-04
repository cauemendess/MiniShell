/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:02:13 by csilva-m          #+#    #+#             */
/*   Updated: 2023/08/18 15:04:31 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	mult;

	mult = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (mult > __INT_MAX__ || mult / nmemb != size)
		return (NULL);
	ptr = (void *)malloc(mult);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, mult);
	return (ptr);
}
