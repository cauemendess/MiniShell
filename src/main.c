/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/02 14:49:19 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	core->invalid = -1;
	get_env_vars(core);
	prompt_loop();
	return (core->exit_status);
}
