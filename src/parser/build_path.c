/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:44:29 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/01 15:41:41 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*build_path(char *cmd)
{
	char	**split_path;
	char	*path_value;
	char	*cmd_path;
	int		i;

	cmd_has_path(cmd);
	if (cmd_has_path(cmd) == 1)
		return (cmd);
	path_value = my_get_env("PATH");
	split_path = ft_split(path_value, ':');
	free (path_value);
	i = 0;
	while (split_path[i] != NULL)
	{
		cmd_path = malloc((ft_strlen(split_path[i]) + ft_strlen(cmd) + 2) * sizeof(char));
		if (!cmd_path)
			return (NULL);
		ft_strlcpy(cmd_path, split_path[i], ft_strlen(split_path[i]) + 1);
		ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], "/", 2);
		ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], cmd, ft_strlen(cmd) + 1);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	ft_free_matrice(split_path);
	free(cmd);
	return (cmd_path);
}

