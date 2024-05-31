/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:15:53 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/31 16:11:28 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_in	*create_redir_in_list(char *file_name, t_type token_type)
{
	t_redir_in *new;
	new = malloc(sizeof(t_redir_in));
	new->file_name = ft_strdup(file_name);
	new->fd = -1;
	new->next = NULL;
}

t_redir_out	*create_redir_out_list(char *file_name, t_type token_type)
{
	t_redir_out *new;
	new = malloc(sizeof(t_redir_out));
	new->file_name = ft_strdup(file_name);
	new->next = NULL;
}

void add_redir_in(t_redir_in **redir, t_redir_in *new)
{
	t_redir_in *cur;
	cur = *redir;
	while(cur->next)
		cur = cur->next;
	cur->next = new;
}

void add_redir_out(t_redir_out **redir, t_redir_out *new)
{
	t_redir_out *cur;
	cur = *redir;
	while(cur->next)
		cur = cur->next;
	cur->next = new;
}
