/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:45:11 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 19:07:22 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	file_exists(char *file);
t_bool	file_readable(char *file);
t_bool	file_writable(char *file);

t_bool	validate_redir_in_file(char *file, int index)
{
	if (file[0] == '\0')
	{
		file_error_ambiguous("Ambiguous redirect", 1, index);
		return (FALSE);
	}
	//if(is_dir(file))
	//{
	//	file_error(file, "Is a directory", 1, index);
	//	return (FALSE);
	//}
	if (!file_exists(file))
	{
		file_error(file, "No such file or directory", 1, index);
		return (FALSE);
	}
	if (!file_readable(file))
	{
		file_error(file, "Permission denied", 1, index);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_redir_out_file(char *file, int index)
{
	if (file[0] == '\0')
	{
		file_error_ambiguous("Ambiguous redirect", 1, index);
		return (FALSE);
	}
	if (file_exists(file))
	{
		if (!file_writable(file))
		{
			file_error(file, "Permission denied", 1, index);
			return (FALSE);
		}
	}
	//else
	//{
	//	//file_error(file, "Permission denied", 1, index);	
	//	get_core()->error.file_error[index] = TRUE;
	//	return (FALSE);
	//}
	//if(is_dir(file))
	//{
	//	file_error(file, "Is a directory", 1, index);
	//	return (FALSE);
	//}
	return (TRUE);
}
