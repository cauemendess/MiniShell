#include "minishell.h"

t_bool	simple_error(void)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strtrim(get_core()->input, " ");
	if (temp[0] == '|')
	{
		ft_putendl_fd("MiniShell: syntax error near unexpected token `|'", 2);
		free(temp);
		return (TRUE);
	}
	while (temp[i])
		i++;
	if (temp[i - 1] == '<' || temp[i - 1] == '>' || temp[i - 1] == '|')
	{
		ft_putendl_fd("MiniShell: syntax error near unexpected token `newline'", 2);
		free(temp);

		return (TRUE);
	}
	free(temp);
	return (FALSE);
}






