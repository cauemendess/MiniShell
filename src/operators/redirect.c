/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:28:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/02 16:56:35 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirects(void)
{
	t_token	*current;

	current = get_core()->token;
	if (current->token == PIPE)
		remove_token(&current->token, current->token);
	while (current && current->token != PIPE)
	{
		if (current->token == HEREDOC)
			handle_heredoc(current, &get_core()->cmd->redir_in);
		else if (current->token == APPEND || current->token == REDIRECT)
			handle_redir_out(current, &get_core()->cmd->redir_out);
		else if (current->token == TRUNC)
			handle_redir_in(current, &get_core()->cmd->redir_in);
		current = current->next;
	}
}

void	handle_heredoc(t_token *token, t_redir_in **redir_list)
{
	t_redir_in	*cur_redir;

	cur_redir = create_redir_in_list("heredoc_tmp", token->token);
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_in(redir_list, cur_redir);
	cur_redir->fd = open(cur_redir->file_name, O_RDONLY);
}

void	handle_redir_in(t_token *token, t_redir_in **redir_list)
{
	t_redir_in	*cur_redir;

	cur_redir = create_redir_in_list(token->next->str, token->token);
	if (!validate_redir_in_file(token->next->str))
	{
		//clear redir list
		return ;
	}
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_in(redir_list, cur_redir);
	cur_redir->fd = open(cur_redir->file_name, O_RDONLY);
}

void	open_redir_out(t_redir_out *redir)
{
	if (redir->tkn_type == APPEND)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND);
	else if (redir->tkn_type == TRUNC)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC);
}

void	handle_redir_out(t_token *token, t_redir_out **redir_list)
{
	t_redir_out	*cur_redir;

	cur_redir = create_redir_out_list(token->next->str, token->token);
	if (!validate_redir_out_file(token->next->str))
	{
		//clear redir list
		return ;
	}
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_out(redir_list, cur_redir);
	open_redir_out(cur_redir);
}
