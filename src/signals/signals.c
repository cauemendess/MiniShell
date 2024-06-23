/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:24:34 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/23 11:30:26 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	get_core()->exit_status = 131;
}

void	signal_handler(void)
{
	struct sigaction	act;
	struct sigaction	ign;

	ft_memset(&act, 0, sizeof(act));
	ft_memset(&ign, 0, sizeof(act));
	ign.sa_handler = SIG_IGN;
	act.sa_sigaction = handler_init;
	sigaction(SIGQUIT, &ign, NULL);
	sigaction(SIGINT, &act, NULL);
}

void	execution_signals(int pid)
{
	if (pid == 0)
	{
		signal(SIGQUIT, handle_quit);
		signal(SIGINT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, handler_exec);
		signal(SIGQUIT, handle_quit);
	}
}

void	handler_exec(int signal)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0 * signal);
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
}
