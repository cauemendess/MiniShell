#include "minishell.h"


void pwd(void)
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	if(cwd == NULL)
	{
		ft_putendl_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		get_core()->exit_status = 1;
	}
	else
	{
		ft_putendl_fd(cwd, 1);
		get_core()->exit_status = 0;
	}
}
