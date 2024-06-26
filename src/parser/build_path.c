/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:44:29 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/16 01:58:49 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_path(char *cmd)
{
	char	**split_env;
	char	*cmd_path;
	int		i;

	if (cmd_has_path(cmd) == 1)
		return (cmd);
	split_env = split_env_path();
	cmd_path = NULL;
	i = 0;
	while (cmd[0] != '\0' && split_env[i] != NULL)
	{
		cmd_path = malloc(
				(ft_strlen(split_env[i]) + ft_strlen(cmd) + 2) * sizeof(char));
		if (!cmd_path)
			return (NULL);
		copy_cmd_path(cmd, cmd_path, split_env[i]);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	ft_free_matrice(split_env);
	free(cmd);
	return (cmd_path);
}

int	cmd_has_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	copy_cmd_path(char *cmd, char *cmd_path, char *split_path)
{
	ft_strlcpy(cmd_path, split_path, ft_strlen(split_path) + 1);
	ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], "/", 2);
	ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], cmd, ft_strlen(cmd) + 1);
}

char	**split_env_path(void)
{
	char	**split_return;
	char	*path_value;

	path_value = my_get_env("PATH");
	split_return = ft_split(path_value, ':');
	free (path_value);
	return (split_return);
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
