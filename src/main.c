/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/23 15:37:49 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

void	save_tty(int tty_fd)
{
	static struct termios	tty;

	if (!tty_fd)
		tcgetattr(STDIN_FILENO, &tty);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	save_tty(0);
	core->invalid = -1;
	get_env_vars(core);
	prompt_loop();
	return (core->exit_status);
}
