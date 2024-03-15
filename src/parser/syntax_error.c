#include "minishell.h"

void	split_quotes(char *str, int * i)
{
	char quote;

	quote = str[*i];
	(*i)++;
	while(str[*i] && str[*i] != quote)
		(*i)++;
}
t_bool	check_start_pipe(void)
{
	t_token *token;
	token = get_core()->token;
	if(token->token == PIPE)
	{
		ft_putendl_fd("MiniShell: syntax error near unexpected token `|'", 2);
		return(TRUE);
	}
	return(FALSE);
}

t_bool	check_pipe_pipe(void)
{
	t_token *cur;
	cur = get_core()->token;
	while(cur)
	{
		if(cur->token == PIPE && cur->next->token == PIPE)
		{
			ft_putendl_fd("MiniShell: syntax error near unexpected token `||'", 2);
			return(TRUE);
		}
		else if ((cur->token == TRUNC || cur->token == APPEND || cur->token == HEREDOC
                || cur->token == WORD) && cur->next->token == PIPE)
		{
			ft_putendl_fd("MiniShell: syntax error near unexpected token `||'", 2);
            return (TRUE);
		}
		cur = cur->next;
	}
	return(FALSE);
}


t_bool	simple_error(void)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strtrim(get_core()->input, " ");
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("MiniShell: syntax error near unexpected token `newline'",
						2);
		free(temp);
		return (TRUE);
	}
	free(temp);
	return (FALSE);
}

char	*get_error_message(char token)
{
	if (token == '&')
		return ("MiniShell: syntax error near unexpected token `&`");
	else if (token == '\\')
		return ("MiniShell: syntax error near unexpected token `\\`");
	else if (token == ';')
		return ("MiniShell: syntax error near unexpected token `;`");
	else
		return (NULL);
}

t_bool	inside_quotes(char *input, int index)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (i < index)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == input[i])
				quote = '\0';
			else if (quote == '\0')
				quote = input[i];
		}
		i++;
	}
	if (quote != '\0')
		return (TRUE);
	return (FALSE);
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
			ft_putendl_fd(error_message, 2);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	open_quotes(void)
{
	char	*input;
	int		open_single;
	int		open_double;
	int		i;

	open_single = 0;
	open_double = 0;
	i = -1;
	input = get_core()->input;
	while (input[++i])
	{
		if (input[i] == '\"' && open_double == 0)
			open_double = 1;
		else if (input[i] == '\"' && open_double == 1)
			open_double = 0;
		else if (input[i] == '\'' && open_single == 0)
			open_single = 1;
		else if (input[i] == '\'' && open_single == 1)
			open_single = 0;
	}
	if (open_single != 0 || open_double != 0)
	{
		ft_putendl_fd("MiniShell: syntax error near unexpected token `);`", 2);
		return (TRUE);
	}
	return (FALSE);
}
