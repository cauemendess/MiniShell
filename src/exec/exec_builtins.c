/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:15:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/25 16:15:22 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(char **args)
{
	t_core *core;
	core = get_core();

	if (strcmp("cd", core->token->str) == 0)
		cd(args);
	else if (strcmp("pwd", core->token->str) == 0)
		pwd(args);
	else if (strcmp("unset", core->token->str) == 0)
		unset(args);
	else if (strcmp("echo", core->token->str) == 0)
		echo(args);
	else if (strcmp("env", core->token->str) == 0)
		env(args);
	else if (strcmp("exit", core->token->str) == 0)
		exit_shell();
}
