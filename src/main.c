#include "minishell.h"


t_core	*get_core(void)
{
	static t_core *core;
	return(&core);
}
t_bool	cat_error(void)
{
	char *temp;
	int i;
	i = 0;
	temp = ft_strtrim(get_core()->input, " ");
	if(temp[0] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		return(TRUE);
	}
	while(temp[i])
		i++;
	if(temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		return(TRUE);
	}
	return (FALSE);
}

int main(void)
{

	t_core *core;
	core = get_core();
	while(1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		add_history(core->input);
		if(!core->input)
			exit(0);
		if(core->input[0] == '\0')
			continue;
		if(cat_error())
			continue ; 
	}
	return(0);
	free(core->input);
}
