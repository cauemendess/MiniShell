/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:32:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/13 14:45:28 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *str);
static int	count_args(char **argv);

void	echo(char **argv, int fd)
{
	int	argc;
	int	flag;
	int	i;

	get_core()->exit_status = 0;
	argc = count_args(argv);
	flag = 0;
	i = 1;
	while (argv[i] && is_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], fd);
		if (i < argc - 1)
			write(fd, " ", 1);
		i++;
	}
	if (!flag)
		write(fd, "\n", 1);
}

static int	is_flag(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] != '-')
		return (flag);
	i++;
	while (str[i])
	{
		if (str[i] == 'n')
			flag = 1;
		else
			return (0);
		i++;
	}
	return (flag);
}

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
