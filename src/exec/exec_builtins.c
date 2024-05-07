/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:15:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/07 15:20:02 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(char **args)
{
	t_core *core;
	core = get_core();

	if (ft_strcmp("cd", core->token->str) == 0)
		cd(args);
	else if (ft_strcmp("pwd", core->token->str) == 0)
		pwd(args);
	else if (ft_strcmp("unset", core->token->str) == 0)
		unset(args);
	else if (ft_strcmp("echo", core->token->str) == 0)
		echo(args);
	else if (ft_strcmp("env", core->token->str) == 0)
		env(args);
	else if (ft_strcmp("exit", core->token->str) == 0)
		exit_shell();
}
