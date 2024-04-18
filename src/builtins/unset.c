/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:09 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/18 15:47:31 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(char *key, t_env **head)
{
	t_env	*env;

	env = *head;
	while (env != NULL && ft_strncmp(env->key, key, ft_strlen(key)) != 0)
		env = env->next;
	if (env == NULL)
		return ;
	if (env->prev != NULL)
		env->prev->next = env->next;
	if (env->next != NULL)
		env->next->prev = env->prev;
	if (*head == env)
		*head = env->next;
	free(env->key);
	free(env->value);
	free(env);
}

void	unset(char **argv)
{
	int	i;

	i = 1;
	get_core()->exit_status = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i][0]))
		{
			printf("unset: `%s': not a valid identifier", argv[i]);
			get_core()->exit_status = 2;
		}
		delete_env(argv[i], &get_core()->env_list);
		i++;
	}
}
