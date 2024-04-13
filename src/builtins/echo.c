/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:32:43 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/13 18:16:09 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_args(char **argv)
{
	int i = 0;
	while(argv[i])
		i++;
	return i;
}

static int is_flag(char *str)
{
	int i = 0;
	int flag = 0;
	if(str[i] != '-')
		return (flag);
	i++;
	while(str[i])
	{
		if(str[i] == 'n')
			flag = 1;
		else
			return (0);
		i++;
	}
	return (flag);
}

void	echo(char **argv)
{
	int argc = count_args(argv);
	int flag = 0;
	int i = 1;

	while(argv[i] && is_flag(argv[i]))
	{
		flag = 1;
		i++;
	}
	while(i < argc)
	{
		printf("%s", argv[i]);
		if(i < argc - 1)
			printf(" ");
		i++;
	}
	if(!flag)
		printf("\n");
	return (0);
}

