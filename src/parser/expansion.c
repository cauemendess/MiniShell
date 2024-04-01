/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/01 17:02:45 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *str)
{
	int		i;
	char	*line;

	line = ft_strchr(str, '$');
	if (!line)
		return (NULL);
	i = 1;
	while (line[i] && (ft_isalnum(line[i])))
		i++;
	if (line[i] == '?')
		i++;
	return (ft_substr(line, 0, i));
}

char	*my_get_env(char *key)
{
	t_env	*env;

	env = get_core()->env_list;
	if (!key)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (ft_strdup(env->value));
		if (!ft_strncmp(key, "?", 2))
			return (ft_itoa(get_core()->exit_status));
		if (!ft_strncmp(key, "$", 3))
			return (ft_strdup("$"));
		env = env->next;
	}
	return (ft_strdup(""));
}

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
		if (str[(*i)] == '$' && str[(*i) + 1] == '?')
			return (TRUE);
		(*i)++;
	}
	return (FALSE);
}

void	parsing_vars(void)
{
	t_token		*cur;
	char		*var;
	static int	status;
	static int	i;

	cur = get_core()->token;
	while (cur)
	{
		if (have_dollar(cur->str, &i, &status))
		{
			garbage_collect(var = find_var(cur->str));
			cur->str = ft_replace(cur->str, var, my_get_env(var + 1));
			cur->token = VAR;
			continue ;
		}
		i = 0;
		remove_quote(cur->str);
		status = 0;
		cur = cur->next;
	}
}


