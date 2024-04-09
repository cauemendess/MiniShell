/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:37 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/09 15:41:56 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_start_pipe(void)
{
	char	*temp;

	temp = get_core()->input;
	ft_strip(temp);
	if (temp[0] == '|')
	{
		error("syntax error: near unexpected token `|'", 2, 2);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_op_op(void)
{
	t_token	*cur;

	cur = get_core()->token;
	while (cur)
	{
		if (cur->token == PIPE && cur->next->token == PIPE)
		{
			error("syntax error: near unexpected token `||'", 2, 2);
			return (TRUE);
		}
		else if ((cur->token == TRUNC || cur->token == APPEND
					|| cur->token == HEREDOC || cur->token == REDIRECT)
				&& cur->next->token != WORD)
		{
			error("syntax error: unexpected token after operator", 2, 2);
			return (TRUE);
		}
		cur = cur->next;
	}
	return (FALSE);
}

t_bool	check_end_op(void)
{
	char	*temp;
	int		i;

	i = 0;
	temp = get_core()->input;
	ft_strip(temp);
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		error("syntax error: near unexpected token `newline'", 2, 2);
		return (TRUE);
	}
	return (FALSE);
}

char	*get_error_message(char token)
{
	if (token == '&')
		return ("syntax error: near unexpected token `&`");
	else if (token == '\\')
		return ("syntax error: near unexpected token `\\`");
	else if (token == ';')
		return ("syntax error: near unexpected token `;`");
	else
		return (NULL);
}

t_bool	forbiden_token(void)
{
	char	*temp;
	int		i;
	char	*error_message;

	i = 0;
	temp = get_core()->input;
	while (temp[i])
	{
		error_message = get_error_message(temp[i]);
		if (temp[i] == '\'' || temp[i] == '"')
			split_quotes(temp, &i);
		if (error_message != NULL)
		{
			error(error_message, 2, 2);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	check_close_quotes(void)
{
	char	*str;
	int		i;

	str = get_core()->input;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			split_quotes(str, &i);
			if (str[i] == '\0')
			{
				error("syntax error: unspected end of file", 2, 2);
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}
