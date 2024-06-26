/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:59:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 18:19:49 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_dir(char *file)
{
	struct stat	statbuf;
	char		*last_slash;
	int			i;

	i = ft_strrchr(file, '/') - file;
	last_slash = ft_substr(file, 0, i);
	if (stat(last_slash, &statbuf) == -1)
	{
		free(last_slash);
		return (FALSE);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		free(last_slash);
		return (TRUE);
	}
	free(last_slash);
	return (FALSE);
}

t_bool	file_exists(char *file)
{
	if (access(file, F_OK) == -1)
		return (FALSE);
	return (TRUE);
}

t_bool	file_readable(char *file)
{
	if (access(file, R_OK) == -1)
		return (FALSE);
	return (TRUE);
}

t_bool	file_writable(char *file)
{
	if (access(file, W_OK) == -1)
		return (FALSE);
	return (TRUE);
}