/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:53 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 17:41:18 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **argv, int fd)
{
	t_env	*stack;

	if (matrice_len(argv) > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		get_core()->exit_status = 127;
		return ;
	}
	stack = get_core()->env_list;
	while (stack)
	{
		if (stack->value != NULL)
		{
			ft_putstr_fd(stack->key, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(stack->value, fd);
		}
		stack = stack->next;
	}
	get_core()->exit_status = 0;
}
