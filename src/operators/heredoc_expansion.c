/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:19:18 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/23 15:21:25 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*has_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?' || ft_isalnum(line[i + 1]))
				return (line + i);
		}
		i++;
	}
	return (NULL);
}

char	*search_var(char *str)
{
	int		i;
	char	*line;

	line = has_var(str);
	if (!line)
		return (NULL);
	i = 1;
	while (line[i] && (ft_isalnum(line[i])))
		i++;
	if (line[i] == '?')
		i++;
	return (ft_substr(line, 0, i));
}

char	*expand_on_heredoc(char *line)
{
	char	*var;

	while (has_var(line))
	{
		garbage_collect(var = search_var(line));
		line = ft_replace(line, var, my_get_env(var + 1));
	}
	return (line);
}
