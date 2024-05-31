/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:05:57 by dfrade            #+#    #+#             */
/*   Updated: 2024/05/31 20:12:10 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(void)
{
	t_token	*list;
	int 	i;
	
	list = get_core()->token;
	if (list == NULL)
		return (0);
	i = 1;
	while (list != NULL)
	{
		if (list->token == (int)PIPE)
			i++;
		list = list->next;
	}
	return (i);
}

char	**cmd_to_matrix(t_token **ptr_token)
{
	t_token	*ptr_token_list;
	char	**matrix;
	int		lenght;
	int		i;

	ptr_token_list = *ptr_token;
	while (ptr_token_list != NULL && ptr_token_list->token != (int)PIPE)
	{
		ptr_token_list = ptr_token_list->next;
		lenght++;
	}
	
	matrix = malloc((lenght + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	
	i = 0;
	ptr_token_list = *ptr_token;
	while (ptr_token_list != NULL && ptr_token_list->token != (int)PIPE)
	{
		matrix[i] = ft_strdup(ptr_token_list->str);
		if (matrix[i] == NULL)
		{
			ft_free_matrice(matrix);
			return (NULL);
		}
		ptr_token_list = ptr_token_list->next;
		i++;
	}
	*ptr_token = ptr_token_list;
	if ((*ptr_token)->token == (int)PIPE)
		*ptr_token = (*ptr_token)->next;
	matrix[i] = NULL;	
	return (matrix);
}

char	**env_to_matrix(void)
{
	char	**env_matrix;
	t_env	*env_list;
	t_env	*temp_count;
	int		lenght;
	int		i;
	
	
	env_list = get_core()->env_list;
	if (env_list == NULL)
		return (NULL);
	
	temp_count = env_list;
	lenght = 0;
	while (temp_count != NULL)
	{
		lenght++;
		temp_count = temp_count->next;
	}

	env_matrix = malloc((lenght + 1) * sizeof(char *));
	if (env_matrix == NULL)
		return (NULL);
	
	i = 0;
	while (env_list != NULL)
	{
		// mallocar
		env_matrix[i] = malloc((ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2) * sizeof(char *));
		if (env_matrix[i] == NULL)
		{
			// free em tudo
			return (NULL);		
		}
		// copiar
		ft_strlcpy(env_matrix[i], env_list->key, ft_strlen(env_list->key) + 1);
		ft_strlcpy(env_matrix[i], "=", 2);
		ft_strlcpy(env_matrix[i], env_list->value, ft_strlen(env_list->value) + 1);
	
		env_list = env_list->next;
		i++;
	}
	env_matrix[i] = NULL;
	return(env_matrix);	
}

t_bool is_builtin(char *cmd)
{
	int	i;
	const char *builtins[] = {"echo", "exit", "pwd", "unset", "export", "env", "cd", NULL};
	
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
