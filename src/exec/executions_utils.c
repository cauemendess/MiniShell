/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:33:24 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/02 16:09:18 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_redirect(int *pipes)
{
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	close(pipes[0]);
}

void	dup_pipes_backup(int pipes_backup)
{
	dup2(pipes_backup, STDIN_FILENO);
	close(pipes_backup);
}

void	update_pipes_backup(int *pipes, int *pipes_backup)
{
	*pipes_backup = pipes[0];
	close(pipes[1]);
}

void	wait_child(t_cmd *cmd_table, int cmd_number)
{
	int	i;

	i = 0;
	while (i < cmd_number)
	{
		waitpid(cmd_table[i].fork_pid, &(get_core()->exit_status), 0);
		i++;
	}
	get_core()->exit_status = WEXITSTATUS(get_core()->exit_status);
}

void	clear_and_exit_child(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	clear_child_exec();
	exit(get_core()->exit_status);
}
