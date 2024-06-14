/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:33 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/13 19:32:47 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_tkn_lst(char *str, int type)
{
	t_token	*node;

	node = ft_calloc(sizeof(t_token), 1);
	node->str = ft_strdup(str);
	node->token = type;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_token(t_token **token, t_token *new)
{
	t_token	*cur;

	if (!*token)
	{
		*token = new;
		return ;
	}
	cur = *token;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	cur->next->prev = cur;
}

void	save_words(char *input, int start, int end)
{
	t_core	*core;
	char	*str;

	core = get_core();
	str = ft_calloc(end - start + 1, sizeof(char));
	ft_memmove(str, &input[start], end - start);
	add_token(&core->token, create_tkn_lst(str, WORD));
	free(str);
}

void	save_separator(char *input, int pos, int type)
{
	char	*str;
	t_core	*core;

	core = get_core();
	if (type == APPEND || type == HEREDOC)
	{
		str = ft_calloc(3, sizeof(char));
		ft_memmove(str, &input[pos], 2);
		add_token(&core->token, create_tkn_lst(str, type));
		free(str);
	}
	else
	{
		str = ft_calloc(2, sizeof(char));
		ft_memmove(str, &input[pos], 1);
		add_token(&core->token, create_tkn_lst(str, type));
		free(str);
	}
}

int	check_token(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, ">", 1))
		return (REDIRECT);
	else if (!ft_strncmp(str, "<", 1))
		return (TRUNC);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(str, " ", 1))
		return (SPACES);
	else if (!ft_strncmp(str, "\0", 1))
		return (END);
	else
		return (0);
}

void	lexing(char *input)
{
	int		type;
	int		start;
	size_t	i;

	start = 0;
	i = -1;
	while (++i < ft_strlen(input) + 1)
	{
		if (input[i] == '\'' || input[i] == '"')
			split_quotes(input, (int *)&i);
		type = check_token(&input[i]);
		if (type)
		{
			if (i != 0 && !check_token(&input[i - 1]))
				save_words(input, start, i);
			if (type != VAR && type != SPACES)
			{
				save_separator(input, i, type);
				if (type == HEREDOC || type == APPEND)
					i++;
			}
			start = i + 1;
		}
	}
}
