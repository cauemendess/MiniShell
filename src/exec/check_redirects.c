/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:39:50 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/13 19:22:02 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirects(t_cmd *cmd)
{
	if (cmd->redir_in)
	{
		dup2(cmd->redir_in->fd, STDIN_FILENO);
		close(cmd->redir_in->fd);
	}
	if (cmd->redir_out)
	{
		dup2(cmd->redir_out->fd, STDOUT_FILENO);
		close(cmd->redir_out->fd);
	}
}
