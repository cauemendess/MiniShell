/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:05:57 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/02 12:40:04 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_to_matrix(t_token **ptr_token)
{
	t_token	*ptr_token_list;
	char	**matrix;
	int		i;

	ptr_token_list = *ptr_token;
	matrix = malloc((cmd_list_lenght(ptr_token_list) + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (ptr_token_list != NULL && ptr_token_list->token != (int)PIPE 
			&& ptr_token_list->token != (int)END)
	{
		matrix[i] = ft_strdup(ptr_token_list->str);
		if (matrix[i++] == NULL)
		{
			ft_free_matrice(matrix);
			return (NULL);
		}
		ptr_token_list = ptr_token_list->next;
	}
	*ptr_token = ptr_token_list;
	if (*ptr_token != NULL && (*ptr_token)->token == (int)PIPE)
		*ptr_token = (*ptr_token)->next;
	matrix[i] = NULL;	
	return (matrix);
}

char	**env_to_matrix(void)
{
	t_env	*env_list;
	char	**env_matrix;
	int		i;
	
	env_list = get_core()->env_list;
	if (env_list == NULL)
		return (NULL);
	env_matrix = malloc((env_list_lenght(env_list) + 1) * sizeof(char *));
	if (env_matrix == NULL)
		return (NULL);
	i = 0;
	while (env_list != NULL)
	{
		env_matrix[i] = malloc((ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2) * sizeof(char *));
		if (env_matrix[i] == NULL)
		{
			ft_free_matrice(env_matrix);
			return (NULL);
		}
		copy_env_matrix(env_matrix[i], env_list);
		env_list = env_list->next;
		i++;
	}
	env_matrix[i] = NULL;
	return(env_matrix);	
}

int	cmd_list_lenght(t_token *token_list)
{
	t_token	*temp_ptr;
	int		lenght;
	
	temp_ptr = token_list;
	lenght = 0;
	while (temp_ptr != NULL 
			&& temp_ptr->token != (int)PIPE
			&& temp_ptr->token != (int)END)
	{
		temp_ptr = temp_ptr->next;
		lenght++;
	}
	return(lenght);
}

int	env_list_lenght(t_env *env_list)
{
	t_env	*temp_ptr;
	int		lenght;

	temp_ptr = env_list;
	lenght = 0;
	while (temp_ptr != NULL)
	{
		lenght++;
		temp_ptr = temp_ptr->next;
	}
	return (lenght);
}

void	copy_env_matrix(char *env_matrix, t_env	*env_list)
{
	ft_strlcpy(env_matrix, env_list->key, ft_strlen(env_list->key) + 1);
	ft_strlcpy(&env_matrix[ft_strlen(env_matrix)], "=", 2);
	ft_strlcpy(&env_matrix[ft_strlen(env_matrix)], env_list->value, ft_strlen(env_list->value) + 1);
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

int	cmd_count(void)
{
	t_token	*list;
	int		i;
	
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
