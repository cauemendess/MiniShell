/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:53 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/06 19:32:27 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **argv)
{
	t_env	*stack;

	if (matrice_len(argv) > 1)
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		get_core()->exit_status = 127;
		return ;
	}
	stack = get_core()->env_list;
	while (stack)
	{
		if (stack->value != NULL)
		{
			ft_putstr_fd(stack->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(stack->value, STDOUT_FILENO);
		}
		stack = stack->next;
	}
	get_core()->exit_status = 0;
}
