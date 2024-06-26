/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:10:40 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 15:33:12 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_redir_out(t_redir_out **redir)
{
	t_redir_out	*cur;
	t_redir_out	*tmp;

	cur = *redir;
	if (cur == NULL)
		return ;
	while (cur)
	{
		tmp = cur->next;
		close(cur->fd);
		free(cur->file_name);
		free(cur);
		cur = tmp;
	}
	*redir = NULL;
}

void	clear_redir_in(t_redir_in **redir)
{
	t_redir_in	*cur;
	t_redir_in	*tmp;

	cur = *redir;
	if (cur == NULL)
		return ;
	while (cur)
	{
		tmp = cur->next;
		close(cur->fd);
		if (access("heredoc_tmp", F_OK) != -1)
			unlink("heredoc_tmp");
		free(cur->file_name);
		free(cur);
		cur = tmp;
	}
	*redir = NULL;
}
