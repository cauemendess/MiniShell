/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/24 17:37:08 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	exec_builtins(char **args);

void	process(void)
{
	t_core	*core;
	char	**args;

	garbage_collect(args = ft_split("env vefv", ' '));
	core = get_core();
	if (syntax_errors())
		return ;
	lexing(core->input);
	if (check_op_op())
		return ;
	parsing_vars();
	exec_builtins(args);
}

t_bool	syntax_errors(void)
{
	if (only_spaces())
		return (TRUE);
	if (check_start_pipe())
		return (TRUE);
	if (check_end_op())
		return (TRUE);
	if (check_close_quotes())
		return (TRUE);
	if (forbiden_token())
		return (TRUE);
	return (FALSE);
}

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