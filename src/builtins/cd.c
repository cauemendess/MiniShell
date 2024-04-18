/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:54 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/18 17:22:27 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)
{
	char	*path;

	if (matrice_len(argv) > 2)
	{
		get_core()->exit_status = 1;
		ft_putendl_fd("cd: too many arguments", 2);
		return ;
	}
	else if (argv[0] == NULL || argv[0][0] == '~')
	{
		path = my_get_env("HOME");
		if (path[0] == '\0')
		{
			get_core()->exit_status = 1;
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = argv[0];
	chdir(path);
}
