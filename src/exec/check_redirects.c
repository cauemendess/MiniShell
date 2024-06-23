/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:39:50 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/23 15:41:44 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirects(t_cmd *cmd)
{
	if (cmd->redir_in != NULL)
	{
		dup2(cmd->redir_in->fd, STDIN_FILENO);
		close(cmd->redir_in->fd);
	}
	if (cmd->redir_out != NULL)
	{
		dup2(cmd->redir_out->fd, STDOUT_FILENO);
		close(cmd->redir_out->fd);
	}
}
