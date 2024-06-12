/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:15:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/12 18:26:19 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_cmd *cmd)
{
	t_core	*core;
	int		fd;
	
	if(cmd->redir_out != NULL)
		fd = cmd->redir_out->fd;
	else
		fd = 1;
	core = get_core();
	
	if (ft_strncmp("cd", core->token->str, 2) == 0)
		cd(cmd->args);
	else if (ft_strncmp("pwd", core->token->str, 3) == 0)
		pwd(cmd->args, fd);
	else if (ft_strncmp("unset", core->token->str, 5) == 0)
		unset(cmd->args);
	else if (ft_strncmp("echo", core->token->str, 4) == 0)
		echo(cmd->args, fd);
	else if (ft_strncmp("env", core->token->str, 3) == 0)
		env(cmd->args, fd);
	else if (ft_strncmp("export", core->token->str, 7) == 0)
		export(cmd->args, fd);
	else if (ft_strncmp("exit", core->token->str, 4) == 0)
		exit_shell();
}
