/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/23 14:27:47 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	exec_builtins(char **args);
t_bool	tokenizer(char *input);

void	process(void)
{
	t_core	*core;
	//char	**args;

	//garbage_collect(args = ft_split("env vefv", ' '));
	core = get_core();
	if (syntax_errors())
		return ;
	if(tokenizer(core->input))
		return ;
	capture_heredoc();
	//if(cmd_parse())
	//	return ;
	//exec_builtins(args);
}

t_bool	tokenizer(char *input)
{
	lexing(input);
	if (check_op_op())
		return (TRUE);
	parsing_vars();
	return(FALSE);
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
