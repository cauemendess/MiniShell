/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:15:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/02 14:46:42 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(char **args)
{
	t_core	*core;

	core = get_core();
	if (ft_strncmp("cd", core->token->str, 2) == 0)
		cd(args);
	else if (ft_strncmp("pwd", core->token->str, 3) == 0)
		pwd(args);
	else if (ft_strncmp("unset", core->token->str, 5) == 0)
		unset(args);
	else if (ft_strncmp("echo", core->token->str, 4) == 0)
		echo(args);
	else if (ft_strncmp("env", core->token->str, 3) == 0)
		env(args);
	else if (ft_strncmp("exit", core->token->str, 4) == 0)
		exit_shell();
}
