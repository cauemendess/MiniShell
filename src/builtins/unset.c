/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:09 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/07 22:30:04 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_unset_error(char *argv);
int		is_var_name_valid(char *var);

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
		if (!(is_var_name_valid(argv[i])))
		{
			print_unset_error(argv[i]);
			get_core()->exit_status = 2;
		}
		delete_env(argv[i], &get_core()->env_list);
		i++;
	}
}

int	is_var_name_valid(char *var)
{
	int	i;

	i = 0;
	if (var[0] != '\0' && (ft_isalpha(var[0]) == 1 || var[0] == '_'))
	{
		while (var[i] != '=' && var[i] != '\0')
		{
			if (ft_isalnum(var[i]) == 1 || var[i] == '_')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	print_unset_error(char *argv)
{
	char	*message;
	
	message = malloc((ft_strlen(argv) + 35 + 1) * sizeof(char));
	if(message == NULL)
		return ;
	ft_strlcpy(message, "unset: `", 9);
	ft_strlcpy(&message[ft_strlen(message)], argv, ft_strlen(argv) + 1);
	ft_strlcpy(&message[ft_strlen(message)], "': not a valid identifier\n", 29);
	write(2, message, ft_strlen(message));
	free(message);
	get_core()->exit_status = 1;
}

