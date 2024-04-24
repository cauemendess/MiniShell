/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:24:34 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/24 17:27:54 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;

	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
}

void signal_handler(void)
{
	struct sigaction act;
	struct sigaction ign;


	ft_memset(&act, 0, sizeof(act));
	ft_memset(&ign, 0, sizeof(act));
	ign.sa_handler = SIG_IGN;
	act.sa_sigaction = handler;
	sigaction(SIGQUIT, &ign, NULL);
	sigaction(SIGINT, &act, NULL);
}
