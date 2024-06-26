/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 00:56:50 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/26 12:02:53 by csilva-m         ###   ########.fr       */
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

void	remove_expansions_to_nothing(void)
{
	t_token	*current;

	current = get_core()->token;
	while (current)
	{
		if (current->token == VAR && current->str[0] == '\0'
			&& current->prev->token != REDIRECT
			&& current->prev->token != APPEND && current->prev->token != TRUNC)
			remove_token(&get_core()->token, current);
		current = current->next;
	}
}

void	process_token(t_token *cur, int *i, int *status)
{
	replace_invalid(cur, get_core()->invalid);
	*i = 0;
	*status = 0;
	remove_quote(cur->str, cur);
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
		if (cur->token == HEREDOC)
		{
			cur = cur->next->next;
			continue ;
		}
		if (have_dollar(cur->str, &i, &status))
		{
			if (mult_dollar(cur->str, &var))
				garbage_collect(var = find_var(cur->str, i));
			cur->str = ft_replace(cur->str, var, my_get_env(var + 1));
			cur->token = VAR;
			continue ;
		}
		process_token(cur, &i, &status);
		cur = cur->next;
	}
}
