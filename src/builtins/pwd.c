/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:57 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/16 01:33:21 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd_error(char *argv);

void	pwd(char **argv, int fd)
{
	char	*cwd;

	if (argv[1])
	{
		if (argv[1][0] == '-')
		{
			print_pwd_error(argv[1]);
			return ;
		}
	}
	cwd = getcwd(NULL, 0);
	ft_putendl_fd(cwd, fd);
	free(cwd);
	get_core()->exit_status = 0;
}

void	print_pwd_error(char *argv)
{
	char	*message;

	message = malloc((ft_strlen(argv) + 24 + 1) * sizeof(char));
	if (message == NULL)
		return ;
	ft_strlcpy(message, "pwd: ", 6);
	ft_strlcpy(&message[ft_strlen(message)], argv, ft_strlen(argv) + 1);
	ft_strlcpy(&message[ft_strlen(message)], ": invalid option\n", 18);
	write(2, message, ft_strlen(message));
	free(message);
	get_core()->exit_status = 2;
}
