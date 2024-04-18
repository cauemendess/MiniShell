/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:48:38 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/18 17:19:22 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>


void	process(void)
{
	t_core	*core;
	char **str;

	str = ft_split("", ' ');
	core = get_core();
	if (syntax_errors())
		return ;
	lexing(core->input);
	if (check_op_op())
		return ;
	parsing_vars();
	if(strcmp("cd", core->token->str) == 0)
		cd(str);
	else if(strcmp("pwd", core->token->str) == 0)
		pwd(str);
	
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
