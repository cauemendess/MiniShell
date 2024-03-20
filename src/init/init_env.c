#include "minishell.h"


void	ft_print_env(void)
{
	int		i;
	t_env	*stack;

	stack = get_core()->env_list;
	i = 0;
	while (stack)
	{
		printf("-----------------------------\n");
		printf("| Key  [%d]:%s.\n", i, stack->key);
		printf("| Value[%d]:%s.\n", i, stack->value);
		printf("| Next [%d]:%p\n", i, stack->next);
		printf("-----------------------------\n");
		i++;
		stack = stack->next;
	}
}


t_env	*create_env_lst(char *key, char *value)
{
	t_env	*node;

	node = ft_calloc(sizeof(t_token), 1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*cur;

	if (!*env)
	{
		*env = new;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	split_env_vars(void)
{
	t_core	*core;
	char	**env;
	char	**split;
	int		i;

	i = 0;
	core = get_core();
	env = core->env;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		add_env(&core->env_list, create_env_lst(split[0], split[1]));
		ft_free_matrice(split);
		i++;
	}
}

void	get_env_vars(t_core *core)
{
	char	**env;
	int		i;

	i = 0;
	while (__environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (__environ[i])
	{
		env[i] = ft_strdup(__environ[i]);
		i++;
	}
	core->env = env;
	split_env_vars();
	ft_free_matrice(env);

}
