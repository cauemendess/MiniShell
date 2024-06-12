/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:57 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/12 17:39:06 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **argv, int fd)
{
	char	*cwd;

	if (argv[1])
	{
		if (argv[1][0] == '-')
		{
			get_core()->exit_status = 2;
			//printf("pwd: %s: invalid option\n", argv[1]);
			ft_putstr_fd("pwd: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": invalid option", 2);
			return ;
		}
	}
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, fd);
	free(cwd);
	get_core()->exit_status = 0;
}
