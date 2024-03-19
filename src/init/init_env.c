#include "minishell.h"

void	get_env_vars(t_core *core)
{
	char	**env;
	int		i;

	i = 0;
	while(__environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	while(__environ[i])
	{
		env[i] = ft_strdup(__environ[i]);
		i++;
	}
	core->env = env;
}
