/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:33:06 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/07 16:19:18 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(void);

void	clear_env_lst(t_env **env)
{
	t_env	*temp;
	char	*temp_key;
	char	*temp_value;

	if (env != NULL)
	{
		while (*env)
		{
			temp_key = (*env)->key;
			temp_value = (*env)->value;
			temp = *env;
			*env = (*env)->next;
			free(temp_key);
			free(temp_value);
			free(temp);
		}
		*env = NULL;
	}
}

void	clear_tkn_lst(t_token **token)
{
	t_token	*temp;
	char	*temp_str;

	if (token != NULL)
	{
		while (*token)
		{
			temp_str = (*token)->str;
			temp = *token;
			*token = (*token)->next;
			free(temp_str);
			free(temp);
		}
		*token = NULL;
	}
}

void	ft_free_matrice(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

void	garbage_collect(void *ptr)
{
	t_list	*gc;

	gc = malloc(sizeof(t_list));
	if (!gc)
		return ;
	gc->content = ptr;
	gc->next = get_core()->garbage;
	get_core()->garbage = gc;
}

void	clear_garbage(void)
{
	t_list	*garbage;
	t_list	*next;

	garbage = get_core()->garbage;
	while (garbage)
	{
		next = garbage->next;
		if (garbage->content != NULL)
			free(garbage->content);
		if (garbage != NULL)
			free(garbage);
		garbage = next;
	}
	get_core()->garbage = NULL;
}

void	remove_token(t_token **list, t_token *target)
{
	t_token *cur;
	cur = *list;
	while(cur)
	{
		if(cur == target)
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
				*list = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			free(cur->str);
			free(cur);
			break;
		}
		cur = cur->next;
	}
}
void	clear_child(void)
{
	if(get_core()->token != NULL)
		clear_tkn_lst(&get_core()->token);
	if(get_core()->env_list)
		clear_env_lst(&get_core()->env_list);
	rl_clear_history();
	
	clear_garbage();
	close_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(get_core()->exit_status);
}

void	close_fds(void)
{
	size_t	index;

	index = 4;
	while (index <= 1024)
	{
		close(index);
		index++;
	}
}
