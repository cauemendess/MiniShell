/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:28:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/28 15:21:14 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirects(void)
{
	t_token *current;
	current = get_core()->token;
	
	if(current->token == PIPE)
		remove_token(&current->token, current->token);
	while(current && current->token != PIPE)
	{
		if(current->token == HEREDOC)
			handle_heredoc(current, &get_core()->cmd->redir_in);
		else if(current->token == APPEND || current->token == REDIRECT)
			handle_redir_out(current);
		else if(current->token == TRUNC)
			handle_redir_in(current);
		current = current->next;
	}
}

void	handle_heredoc(t_token *token, t_redir_in **redir_list)
{
	t_redir_in *cur_redir;
	cur_redir = *redir_list;
	
	if(cur_redir->next == NULL)
	{
		create_redir_in_list("heredoc_tmp", token->token);
	}
}

//void	handle_redir_out(t_token *token, t_redir_out **redir_list)
//{
	
//}


//void	handle_redir_in(t_token *token, t_redir_in **redir_list)
//{
	
//}
