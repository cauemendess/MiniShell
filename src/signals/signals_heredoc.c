/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 00:44:45 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/16 01:37:38 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int pid)
{
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, ctrl_c_heredoc);
}

void	ctrl_c_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
}
