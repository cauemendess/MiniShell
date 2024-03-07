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
		return (TRUE);
	}
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		return (TRUE);
	}
	return (FALSE);
}


char	*replace_occ(char *res, char *ptr, char *old, char *new)
{
	size_t	len;
	char	*subtemp;
	char	*tmp;

	len = ptr - res;
	subtemp = ft_substr(res, 0, len);
	tmp = ft_strjoin(subtemp, new);
	free(subtemp);
	subtemp = ft_strjoin(tmp, ptr + ft_strlen(old));
	free(res);
	free(tmp);
	return (subtemp);
}

char	*ft_replace(char *str, char *old, char *replace)
{
	char	*ptr;
	char	*res;
	size_t	len_str;
	size_t	count;

	len_str = ft_strlen(str);
	res = ft_strdup(str);
	ptr = res;
	while (*ptr)
	{
		ptr = ft_strstr(ptr, old);
		if (!ptr)
			break ;
		count = ptr - res;
		res = replace_occ(res, ptr, old, replace);
		ptr += count + ft_strlen(replace);
	}
	//free(str);
	return (res);
}

void	lexing(void)
{

	char	c;
	char	d;
	char	*str;
	char *temp;

	c = -1;
	d = -2;
	temp = ft_calloc(1, 2);
	temp[0] = c;

	str = get_core()->input;
	str = ft_replace(str, ">", temp);
	printf("[%s]\n", str);
}

void	process(void)
{
	if (!simple_error())
		return ;
	//if(!check_quotes())
	//	return ;
}

void	readlines(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		core->input = readline(COLOR_PINK "MINI_SHELL:" COLOR_RESET " ");
		lexing();
		//add_history(core->input);
		//if (!core->input)
		//	exit(0);
		//if (core->input[0] == '\0')
		//	continue ;
		//process();
	}
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	readlines();
	free(core->input);
}
