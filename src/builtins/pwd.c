/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:57 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/01 11:33:40 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(void)
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	if(cwd == NULL)
	{
		ft_putendl_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		get_core()->exit_status = 1;
	}
	else
	{
		ft_putendl_fd(cwd, 1);
		get_core()->exit_status = 0;
	}
}
