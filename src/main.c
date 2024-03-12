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
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
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

void	clear_tkn_lst(t_token **token)
{
	t_token	*temp;

	if (token != NULL)
	{
		while (*token)
		{
			temp = *token;
			*token = (*token)->next;
			free(temp);
		}
		*token = NULL;
	}
}

void	readlines(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		process();
		ft_print_stack();

		add_history(core->input);
		if (!core->input)
			exit(0);
		if (core->input[0] == '\0')
			continue ;
		clear_tkn_lst(&core->token);
	}
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	readlines();
	free(core->input);
}
