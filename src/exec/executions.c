/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:12:19 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/26 19:04:42 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_number(void)
{
	int	cmd_number;

	cmd_number = cmd_count();
	fill_cmd_table();
	if (cmd_number == 1)
	{
		signal(SIGQUIT, print_quit_or_int);
		signal(SIGINT, print_quit_or_int);
		exec_one_cmd(get_core()->cmd_table);
	}
	else if (cmd_number > 1)
	{
		exec_mult_cmd(cmd_number);
		wait_child(get_core()->cmd_table, cmd_number);
	}
}

void	exec_one_cmd(t_cmd *cmd_table)
{
	int	fork_pid;

	if (get_core()->error.cmd_error[cmd_table->index])
		return ;
	if (cmd_table->is_builtin == TRUE)
		exec_builtins(cmd_table);
	else
	{
		fork_pid = fork();
		execution_signals(fork_pid);
		if (fork_pid == 0)
		{
			if (cmd_table->cmd == NULL)
				clear_and_exit_child(get_core()->exit_status);
			check_redirects(cmd_table);
			cmd_table->cmd = build_path(cmd_table->cmd);
			check_exec(cmd_table);
			execve(cmd_table->cmd, cmd_table->args, cmd_table->envp);
			clear_and_exit_child(get_core()->exit_status);
		}
		waitpid(fork_pid, &get_core()->exit_status, 0);
		return_exit_status();
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
		execution_signals(cmd_table[i].fork_pid);
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
}

void	child_exec(t_cmd *cmd_table, int pipes_backup)
{
	if (pipes_backup != STDIN_FILENO)
		dup_pipes_backup(pipes_backup);
	exec_one_cmd(cmd_table);
	clear_and_exit_child(get_core()->exit_status);
}

void	check_exec(t_cmd *cmd_table)
{
	struct stat	cmd_is_dir;

	if (cmd_table->cmd == NULL)
	{
		write(2, "Command not found\n", 19);
		clear_and_exit_child(127);
	}
	if (access(cmd_table->cmd, F_OK) != 0)
	{
		write(2, "No such file or directory\n", 27);
		clear_and_exit_child(127);
	}
	stat(cmd_table->cmd, &cmd_is_dir);
	if (S_ISDIR(cmd_is_dir.st_mode) != 0)
	{
		write(2, "Is a directory\n", 16);
		clear_and_exit_child(126);
	}
	if (access(cmd_table->cmd, X_OK) != 0)
	{
		write(2, "Permission denied\n", 19);
		clear_and_exit_child(126);
	}
}
