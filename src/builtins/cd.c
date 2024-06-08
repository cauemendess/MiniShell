/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:54 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/08 12:42:50 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_path(char *path);

void	cd(char **argv)
{
	char	*path;
	//char	*oldpwd;
	if (matrice_len(argv) > 2)
	{
		error("cd: too many arguments", 1, 1);
		return ;
	}
	else if (argv[0] == NULL || argv[0][0] == '~')
	{
		garbage_collect(path = my_get_env("HOME"));
		if (path[0] == '\0')
		{
			error("cd: HOME not set", 1, 1);
			return ;
		}
	}
	else if (argv[0][0] == '-')
	{
		garbage_collect(path = my_get_env("OLDPWD"));
		if (path[0] == '\0')
		{
			error("cd: OLDPWD not set", 1, 1);
			return ;
		}
	}
	else
		path = argv[0];
	chdir(path);
}

t_bool	is_path(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) == -1)
	{
		error("cd: No such file or directory", 1, 1);
		return (FALSE);
	}
	if (lstat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (TRUE);
		else
		{
			error("cd: Not a directory", 1, 1);
			return (FALSE);
		}
	}
	return (FALSE);
}

