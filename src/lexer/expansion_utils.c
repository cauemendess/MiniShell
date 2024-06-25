/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/24 20:59:20 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	have_dollar(char *str, int *i, int *status)
{
	while (str[(*i)])
	{
		(*status) = ft_quotes_status(str[(*i)], (*status));
		if (str[(*i)] == '$' && str[(*i) + 1] == '$' && ((*status) == 0
				|| (*status) == 1))
		{
			(*i)++;
			return (TRUE);
		}
		if (str[(*i)] == '$' && ((*status) == 0 || (*status) == 1)
			&& ft_isalpha(str[(*i) + 1]))
			return (TRUE);
		if (str[(*i)] == '$' && str[(*i) + 1] == '?'
			&& (*status == 0 || *status == 1))
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

t_bool	mult_dollar(char *str, char **var)
{
	int		i;
	char	*line;

	i = 0;
	line = str;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			line = ft_strchr(line, '$');
			(*var) = ft_substr(line, 0, 2);
			return (FALSE);
		}
		line++;
		i++;
	}
	return (TRUE);
}

void	replace_invalid(t_token *cur, char c)
{
	int	i;

	i = 0;
	while (cur->str[i])
	{
		if (cur->str[i] == c)
			cur->str[i] = '$';
		i++;
	}
}
