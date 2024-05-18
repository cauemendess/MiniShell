/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/18 17:06:43 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes_status(char c, int status)
{
	if (c == '\'' && status == 0)
		status = 2;
	else if (c == '\'' && status == 2)
		status = 0;
	else if (c == '"' && status == 0)
		status = 1;
	else if (c == '"' && status == 1)
		status = 0;
	return (status);
}

void	remove_quote(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			while (*str != '\'')
				str++;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else if (*str == '\"')
		{
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
			while (*str != '\"')
				str++;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
}

void	split_quotes(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
}
