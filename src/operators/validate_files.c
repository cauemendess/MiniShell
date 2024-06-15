/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:45:11 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/08 16:36:22 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	file_exists(char *file);
t_bool	file_readable(char *file);
t_bool	file_writable(char *file);

t_bool	validate_redir_in_file(char *file)
{
	if (!file_exists(file))
	{
		error("No such file or directory", 1, 2);
		return (FALSE);
	}
	if (!file_readable(file))
	{
		error("Permission denied", 1, 2);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_redir_out_file(char *file)
{
	if (file_exists(file))
	{
		if (!file_writable(file))
		{
			error("Permission denied", 1, 2);
			return (FALSE);
		}
	}
	return (TRUE);
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
