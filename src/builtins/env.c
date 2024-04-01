/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:53 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/01 16:58:50 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env(void)
{
	t_env	*stack;

	stack = get_core()->env_list;
	while (stack)
	{
		ft_putstr_fd(stack->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(stack->value, 1);
		stack = stack->next;
	}
	get_core()->exit_status = 0;
}
