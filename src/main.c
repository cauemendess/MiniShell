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


void	process(void)
{
	t_core	*this;

	this = get_core();
	if (only_spaces())
		return ;
	if(check_start_pipe())
		return ;
	if (check_end_op())
		return ;
	if(check_close_quotes())
		return ;
	if(forbiden_token())
		return ;
	lexing(this->input);
	if(check_op_op())
		return ;
	parsing_vars();
}

void	readlines(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL$" COLOR_RESET " ");
		if (!core->input)
			break ;
		if (core->input[0] == '\0')
		{
			free(core->input);
			continue ;
		}

		add_history(core->input);
		process();
		ft_print_stack();
		free(core->input);
		clear_tkn_lst(&core->token);
	}
	clear_garbage();
	free(core->input);
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	core->exit_status = 0;
	get_env_vars(core);
	//ft_print_env();


	readlines();

	
}
