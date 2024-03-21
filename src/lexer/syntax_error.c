#include "minishell.h"


void	split_quotes(char *str, int *i)
{
	char quote;
	quote = str[*i];
	(*i)++;
	while(str[*i] && str[*i] != quote)
		(*i)++;
}

t_bool	check_start_pipe(void)
{
	char *temp;
	temp = get_core()->input;
	ft_strip(temp);
	if(temp[0] == '|')
	{
		get_core()->exit_status = 2;
		ft_putendl_fd("syntax error: near unexpected token `|'", 2);
		return(TRUE);
	}
	return(FALSE);
}

t_bool	check_op_op(void)
{
	t_token *cur;
	cur = get_core()->token;
	while(cur)
	{
		if(cur->token == PIPE && cur->next->token == PIPE)
		{
			get_core()->exit_status = 2;
			ft_putendl_fd("syntax error: near unexpected token `||'", 2);
			return(TRUE);
		}
		else if ((cur->token == TRUNC || cur->token == APPEND || cur->token == HEREDOC || cur->token == PIPE) \
        && cur->next->token != WORD)
		{
			get_core()->exit_status = 2;
			ft_putendl_fd("syntax error: unexpected token after operator", 2);
            return (TRUE);
		}
		cur = cur->next;
	}
	return(FALSE);
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
		get_core()->exit_status = 2;
		ft_putendl_fd("syntax error: near unexpected token `newline'",
						2);
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
			get_core()->exit_status = 2;
			ft_putendl_fd(error_message, 2);
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
                ft_putendl_fd("syntax error: unspected end of file", 2);
				get_core()->exit_status = 2;
				return (TRUE);
            }
		}
		i++;
	}
	return (FALSE);
}
