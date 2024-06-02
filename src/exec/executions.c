/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:12:19 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/02 16:14:33 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_number(void)
{
	int	cmd_number;

	cmd_number = cmd_count();
	fill_cmd_table();
	if (cmd_number == 1)
		exec_one_cmd(get_core()->cmd_table);
	else if (cmd_number > 1)
		exec_mult_cmd(cmd_number);
}

void	exec_one_cmd(t_cmd *cmd_table)
{
	int	fork_pid;

	if (cmd_table->is_builtin == TRUE)
		exec_builtins(cmd_table->args);
	else
	{	
		fork_pid = fork();
		if (fork_pid == 0)
		{
			// execução de redirect
			cmd_table->cmd = build_path(cmd_table->cmd);
			check_exec(cmd_table);
			execve(cmd_table->cmd, cmd_table->args, cmd_table->envp);
			exit(1);
		}
		waitpid(fork_pid, &get_core()->exit_status, 0);
		get_core()->exit_status = WEXITSTATUS(get_core()->exit_status);
	}
}

void	exec_mult_cmd(int cmd_number)
{
	int		i;
	int		pipes[2];
	int		pipes_backup;
	t_cmd	*cmd_table;

	i = -1;
	cmd_table = get_core()->cmd_table;
	pipes_backup = STDIN_FILENO;
	while (++i < cmd_number)
	{
		if (i < cmd_number - 1)
			pipe(pipes);
		cmd_table[i].fork_pid = fork();
		if (cmd_table[i].fork_pid == 0)
		{
			if (i < cmd_number - 1)
				pipe_redirect(pipes);
			child_exec(&cmd_table[i], pipes_backup);
		}
		if (pipes_backup != 0)
			close(pipes_backup);
		if (i < cmd_number - 1)
			update_pipes_backup(pipes, &pipes_backup);
	}
	wait_child(cmd_table, cmd_number);
}

void	child_exec(t_cmd *cmd_table, int pipes_backup)
{
	if (pipes_backup != STDIN_FILENO)
		dup_pipes_backup(pipes_backup);
	exec_one_cmd(cmd_table);
	clear_and_exit_child();
}

void	check_exec(t_cmd *cmd_table)
{
	struct stat	cmd_is_dir;

	if (cmd_table->cmd == NULL)
	{
		write(2, "A utility to be executed was not found.\n", 40);
		exit(127);
	}
	stat(cmd_table->cmd, &cmd_is_dir);
	if (S_ISDIR(cmd_is_dir.st_mode) != 0)
	{
		write(2, "A file to be executed was found, " \
			"but it was not an executable utility.\n", 71);
		exit(126);
	}
	if (access(cmd_table->cmd, X_OK) != 0)
	{
		write(2, "A file to be executed was found, " \
			"but it was not an executable utility.\n", 71);
		exit(126);
	}
}
