/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:28:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 19:06:54 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_token *token, t_redir_in **redir_list);
void	handle_redir_out(t_token *token, t_redir_out **redir_list, int index);

t_token	*handle_redirects(t_cmd *cmd, t_token *current, int index)
{
	t_token	*start_bkp;
	t_token	*next;

	start_bkp = current;
	while ((current) && (current)->token != PIPE)
	{
		next = (current)->next;
		if (is_redir_token((current)))
		{
			if ((current)->token == HEREDOC)
				handle_heredoc((current), &cmd->redir_in);
			else if ((current)->token == APPEND || (current)->token == REDIRECT)
				handle_redir_out((current), &cmd->redir_out, index);
			else if ((current)->token == TRUNC)
				handle_redir_in((current), &cmd->redir_in, index);
			// Se o fd do redir é -1, dar free em todos os nós de redirects desse comando e ir para o próximo
			next = (current)->next->next;
			remove_token(&get_core()->token, (current)->next);
			remove_token(&get_core()->token, (current));
			if (start_bkp == current)
				start_bkp = next;
		}
		(current) = next;
	}
	current = start_bkp;
	return (start_bkp);
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

void	handle_redir_in(t_token *token, t_redir_in **redir_list, int index)
{
	t_redir_in	*cur_redir;

	if (!validate_redir_in_file(token->next->str, index)
		|| get_core()->error.file_error[index])
	{
		clear_redir_in(redir_list);
		return ;
	}
	cur_redir = create_redir_in_list(token->next->str, token->token);
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_in(redir_list, cur_redir);
	cur_redir->fd = open(cur_redir->file_name, O_RDONLY);
}

void	open_redir_out(t_redir_out *redir)
{
	if (redir->tkn_type == APPEND)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->tkn_type == REDIRECT)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	handle_redir_out(t_token *token, t_redir_out **redir_list, int index)
{
	t_redir_out	*cur_redir;

	if (!validate_redir_out_file(token->next->str, index)
		|| get_core()->error.file_error[index])
	{
		clear_redir_out(redir_list);
		return ;
	}
	cur_redir = create_redir_out_list(token->next->str, token->token);
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_out(redir_list, cur_redir);
	open_redir_out(cur_redir);
	if (cur_redir->fd == -1)
	{
		*redir_list = create_redir_out_list(token->next->str, token->token);
		get_core()->error.file_error[index] = TRUE;
		perror(cur_redir->file_name);
		clear_redir_out(redir_list);
	}
}
