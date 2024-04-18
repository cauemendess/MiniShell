/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:57 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/18 15:47:36 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **argv)
{
	char	*cwd;

	if (argv[1])
	{
		if (argv[1][0] == '-')
		{
			get_core()->exit_status = 2;
			printf("pwd: %s: invalid option\n", argv[1]);
			return ;
		}
	}
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, 1);
	get_core()->exit_status = 0;
}
