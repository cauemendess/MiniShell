#include "minishell.h"

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}
t_bool	simple_error(void)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strtrim(get_core()->input, " ");
	if (temp[0] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		free(temp);
		return (TRUE);
	}
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		free(temp);

		return (TRUE);
	}
	free(temp);
	return (FALSE);
}


//void	add_token(char *command, int type)
//{

//}

void	save_words(char *input, int start, int end)
{
	char *str;
	str = malloc(start - end * sizeof(char));
	
	add_token(str, 0);
	free(str);

}

void	save_separator(char *input, int pos, int type)
{
	char *str;
	if(type == APPEND || type == HEREDOC)
	{
		str = malloc(3 * sizeof(char));
		add_token();
		free(str);
	}
	else
	{
		str = malloc(2 * sizeof(char));
		add_token();
		free(str);
	}
}


int	check_token(char *str)
{
	if(!ft_strncmp(str, ">>", 2))
		return(APPEND);
	else if(!ft_strncmp(str, "<<", 2))
		return(HEREDOC);
	else if(!ft_strncmp(str, ">", 1))
		return (REDIRECT);
	else if(!ft_strncmp(str, "<", 1))
		return(TRUNC);
	else if(!ft_strncmp(str, "|", 1))
		return(PIPE);
	else if(!ft_strncmp(str, " ", 1))
		return(SPACES);
	else
		return(0);
	
}

void	lexing(char *input)
{
	int	type;
	int start = 0;
	int i;
	i = -1;
	while (++i < ft_strlen(input) + 1)
	{
		type = check_token(&input[i]);
		if(type)
		{
			if(type != VAR && type != SPACES)
			{
				save_separator(input, i, type);
				i++;
				if(type == HEREDOC || type == APPEND)
					i++;
			}
			if(!check_token(&input[i - 1]) && i != 0)
				save_words(input, start, i);
		}
		start = i;
	}
}

void	process(void)
{
	t_core *this;
	this = get_core();
	if (simple_error())
		return ;
	//if(!check_quotes())
	//	return ;
	lexing(this->input);
}

void	readlines(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		process();
		add_history(core->input);
		if (!core->input)
			exit(0);
		if (core->input[0] == '\0')
			continue ;
	}
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	readlines();
	free(core->input);
}
