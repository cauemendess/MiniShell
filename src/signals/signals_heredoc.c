/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 00:44:45 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/26 14:17:50 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	get_core()->is_heredoc = TRUE;
	get_core()->exit_status = 130;
	close(get_core()->doc_fd);
	clear_child();
}
