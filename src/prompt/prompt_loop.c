/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:42:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/20 16:13:47 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_loop(void)
{
	t_core	*core;

	core = get_core();
	while (1)
	{
		signal_handler();
		ft_bzero(&core->error.cmd_error, 4096);
		ft_bzero(&core->error.file_error, 4096);
		core->is_heredoc = FALSE;
		core->input = readline(COLOR_PINK "MINI_SHELL$" COLOR_RESET " ");
		garbage_collect(core->input);
		if (!core->input)
		{
			clear_garbage();
			break ;
		}
		if (core->input[0] == '\0')
			continue ;
		add_history(core->input);
		process();
		clear_tkn_lst(&core->token);
		clear_garbage();
		clear_cmd_table(core->cmd_table);
	}
	write(1, "exit\n", 5);
	clear_env_lst(&core->env_list);
	rl_clear_history();
}
