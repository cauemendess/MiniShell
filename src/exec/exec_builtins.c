/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:15:19 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/15 19:52:00 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_cmd *cmd)
{
	int		fd;

	if (cmd->redir_out != NULL)
		fd = cmd->redir_out->fd;
	else
		fd = 1;
	if (ft_strncmp("cd", cmd->cmd, 2) == 0)
		cd(cmd->args);
	else if (ft_strncmp("pwd", cmd->cmd, 3) == 0)
		pwd(cmd->args, fd);
	else if (ft_strncmp("unset", cmd->cmd, 5) == 0)
		unset(cmd->args);
	else if (ft_strncmp("echo", cmd->cmd, 4) == 0)
		echo(cmd->args, fd);
	else if (ft_strncmp("env", cmd->cmd, 3) == 0)
		env(cmd->args, fd);
	else if (ft_strncmp("export", cmd->cmd, 7) == 0)
		export(cmd->args, fd);
	else if (ft_strncmp("exit", cmd->cmd, 4) == 0)
		exit_shell(cmd->args);
}
