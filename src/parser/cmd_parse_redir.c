/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:10:22 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/13 19:13:59 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_last_redir_in(t_redir_in **redir)
{
	t_redir_in	*cur;
	t_redir_in	*next;

	if (!redir || !*redir)
		return ;
	cur = *redir;
	while (cur->next)
	{
		next = cur->next;
		if (cur->tkn_type == HEREDOC)
		{
			close(cur->fd);
			unlink("heredoc_tmp");
		}
		else if (cur->tkn_type == TRUNC)
			close(cur->fd);
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*redir = cur;
}

void	save_last_redir_out(t_redir_out **redir)
{
	t_redir_out	*cur;
	t_redir_out	*next;

	if (!redir || !*redir)
		return ;
	cur = *redir;
	while (cur->next)
	{
		next = cur->next;
		if (cur->tkn_type == REDIRECT || cur->tkn_type == APPEND)
		{
			close(cur->fd);
			free(cur->file_name);
			free(cur);
		}
		cur = next;
	}
	*redir = cur;
}
