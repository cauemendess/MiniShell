/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:33 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/01 12:02:52 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_translate_type(int type, int i)
{
	printf("| Type [%d]:", i);
	if (type == 1)
		printf("WORD \n");
	else if (type == 2)
		printf("REDIRECT \n");
	else if (type == 3)
		printf("APPEND \n");
	else if (type == 4)
		printf("PIPE \n");
	else if (type == 5)
		printf("HEREDOC \n");
	else if (type == 6)
		printf("SPACES \n");
	else if (type == 7)
		printf("VAR\n");
	else if (type == 8)
		printf("TRUNC \n");
	else if (type == 9)
		printf("END \n");
}

void	ft_print_stack(void)
{
	int		i;
	t_token	*stack;

	stack = get_core()->token;
	i = 0;
	while (stack)
	{
		printf("-----------------------------\n");
		printf("| Token[%d]:%s.\n", i, stack->str);
		ft_translate_type(stack->token, i);
		printf("| Next [%d]:%p\n", i, stack->next);
		printf("| Prev [%d]:%p\n", i, stack->prev);
		printf("-----------------------------\n");
		i++;
		stack = stack->next;
	}
}

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
		if(input[i] == '\'' || input[i] == '"')
			split_quotes(input, (int *)&i);
		type = check_token(&input[i]);
		if (type)
		{
			if(!check_token(&input[i - 1]) && i != 0)
				save_words(input, start, i);
			if(type != VAR && type != SPACES)
			{
				save_separator(input, i, type);
				if (type == HEREDOC || type == APPEND)
					i++;
			}
			start = i + 1;
		}
	}
}
