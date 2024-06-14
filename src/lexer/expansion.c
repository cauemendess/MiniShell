/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/14 19:52:07 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *str, int j)
{
	int		i;
	char	*line;

	line = str;
	line += j;
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
			return (ft_strdup(&get_core()->invalid));
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
			if (mult_dollar(cur->str, &var))
				garbage_collect(var = find_var(cur->str, i));
			cur->str = ft_replace_index(cur->str, var, my_get_env(var + 1), i);
			cur->token = VAR;
			continue ;
		}
		replace_invalid(cur, get_core()->invalid);
		i = 0;
		status = 0;
		remove_quote(cur->str);
		cur = cur->next;
	}
}
