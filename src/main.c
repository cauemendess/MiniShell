#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

t_bool	only_spaces(void)
{
	unsigned long	i;
	char			*line;

	line = get_core()->input;
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

//t_bool	parser(void)
//{
//	if(simple_error())
//		return(FALSE);
//	lexing(get_core()->input);
//}

void	process(void)
{
	t_core	*this;

	this = get_core();
	if (only_spaces())
		return ;
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
		if (!core->input)
			break ;
		if (core->input[0] == '\0')
		{
			free(core->input);
			continue ;
		}
		process();
		ft_print_stack();
		add_history(core->input);
		free(core->input);
		clear_tkn_lst(&core->token);
	}
	free(core->input);
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	readlines();
}
