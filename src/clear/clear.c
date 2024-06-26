/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:33:06 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 19:14:24 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (matrice == NULL)
		return ;
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
