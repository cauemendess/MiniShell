/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_executions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:40:16 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/24 20:55:08 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_exit_status(void)
{
	if (WIFSIGNALED(get_core()->exit_status))
	{
		if (__WCOREDUMP(get_core()->exit_status))
		{
			get_core()->exit_status = 131;
			return ;
		}
		else if (WTERMSIG(get_core()->exit_status) == SIGINT)
		{
			get_core()->exit_status = 130;
			return ;
		}
	}
	get_core()->exit_status = WEXITSTATUS(get_core()->exit_status);
}
