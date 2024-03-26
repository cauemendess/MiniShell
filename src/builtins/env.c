#include "minishell.h"

void env(void)
{
	t_env	*stack;

	stack = get_core()->env_list;
	while (stack)
	{
		//fd está errado
		printf("%s=%s\n", stack->key, stack->value);
		stack = stack->next;
	}
	get_core()->exit_status = 0;
}
