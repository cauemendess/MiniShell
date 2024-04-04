/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:42:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/04 18:42:49 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_loop(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		//signal_handler();
		garbage_collect(core->input = readline(COLOR_PINK "MINI_SHELL$" COLOR_RESET " "));
		if (!core->input)
			exit_shell();
		if (core->input[0] == '\0')
			continue ;

		add_history(core->input);
		process();
		ft_print_stack();
		clear_tkn_lst(&core->token);
		clear_garbage();
	}
	rl_clear_history();
}
