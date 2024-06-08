/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:28:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/08 17:28:45 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_heredoc(t_token *token, t_redir_in **redir_list);
void	handle_redir_out(t_token *token, t_redir_out **redir_list);

void	print_redirects(t_cmd *cmd)
{
	t_redir_in *redir_in;
	t_redir_out *redir_out;
	
	printf("======== REDIR_IN LIST =============\n");
	redir_in = cmd->redir_in;
	while(redir_in)
	{
		printf("file name: %s\n", redir_in->file_name);
		printf("type: %d\n", redir_in->tkn_type);
		printf("fd: %d\n", redir_in->fd);
		printf("=========================\n");

		redir_in = redir_in->next;
	}
	printf("======== REDIR_OUT LIST ============\n");
	redir_out = cmd->redir_out;
	while(redir_out)
	{
		printf("file name: %s\n", redir_out->file_name);
		printf("type: %d\n", redir_out->tkn_type);
		printf("fd: %d\n", redir_out->fd);
		printf("=========================\n");
		redir_out = redir_out->next;
	}	
}


t_bool	is_redir_token(t_token *token)
{
	if (token->token == REDIRECT || token->token == APPEND
		|| token->token == TRUNC
		|| token->token == HEREDOC)
		return (TRUE);
	return (FALSE);
}

void	handle_redirects(t_cmd *cmd)
{
	t_token	*current;
	t_token *next;
	current = get_core()->token;
	if (current->token == PIPE)
		remove_token(&get_core()->token, current);
	current = get_core()->token;
	while (current && current->token != PIPE)
	{
		next = current->next;
		if(is_redir_token(current))
		{
			if (current->token == HEREDOC)
				handle_heredoc(current, &cmd->redir_in);
			else if (current->token == APPEND || current->token == REDIRECT)
				handle_redir_out(current, &cmd->redir_out);
			else if (current->token == TRUNC)
				handle_redir_in(current, &cmd->redir_in);
			next = current->next->next;
			remove_token(&get_core()->token, current->next);
			remove_token(&get_core()->token, current);
		}
		current = next;
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
		clear_redir_in(redir_list);
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
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->tkn_type == REDIRECT)
		redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		
}

void	handle_redir_out(t_token *token, t_redir_out **redir_list)
{
	t_redir_out	*cur_redir;

	cur_redir = create_redir_out_list(token->next->str, token->token);
	if (!validate_redir_out_file(token->next->str))
	{
		clear_redir_out(redir_list);
		return ;
	}
	if (redir_list == NULL)
		*redir_list = cur_redir;
	else
		add_redir_out(redir_list, cur_redir);
	open_redir_out(cur_redir);
}
