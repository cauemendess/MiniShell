/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:24:34 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/24 19:30:21 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_signals(int pid)
{
	if (pid == 0)
	{
		signal(SIGQUIT, handle_quit);
		signal(SIGINT, handle_quit);
	}
}

void	handler_exec(int signal)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0 * signal);
}

void	handle_quit(int sig)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	clear_child_exec();
	if (sig == SIGINT)
		get_core()->exit_status = 130;
	if (sig == SIGQUIT)
		get_core()->exit_status = 131;
}

void	handler_init(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_core()->exit_status = 130;
}

void	print_quit_or_int(int s)
{
	if (s == SIGQUIT)
		ft_putstr_fd("\nQuit (core dumped)\n", 2);
	if (s == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
