/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/31 20:51:31 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_cmd_number(void)
{
	int cmd_number;

	cmd_number = cmd_count();
	if (cmd_number == 0)
		clear_garbage(); // escolher a função correta para free em tudo até aqui
	else if (cmd_number == 1)
		exec_one_cmd(get_core()->cmd_table);
	else if (cmd_number > 1)
		exec_mult_cmd(cmd_number);
	//free nas coisas que tem que dar free
}

void exec_one_cmd(t_cmd *cmd_table)
{
	int	fork_pid;
	
	if (cmd_table->is_builtin == TRUE)
		exec_builtins(cmd_table->args);
	else
	{	
		fork_pid = fork();
		if (cmd_table->fork_pid == 0)
		{
			// execução de redirect

			cmd_table->cmd = build_path(cmd_table->cmd);
			if (cmd_table->cmd == NULL)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // qual exit?
			}
			
			struct stat	cmd_is_dir;
			stat(cmd_table->cmd, &cmd_is_dir);
			if (S_ISDIR(cmd_is_dir.st_mode) != 0)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // qual exit?
			}

			if (access(cmd_table->cmd, X_OK) != 0)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // qual exit?
			}
			
			execve(cmd_table->cmd, cmd_table->args, cmd_table->envp);
			// free em tudo
			
			exit(126); // qual exit?
		}
		wait(&get_core()->exit_status);
	}
}

void	exec_mult_cmd(int cmd_number)
{
	int		i;
	int		cmd_number_2;
	int		pipes[2];
	int		pipes_backup;
	// t_cmd	*cmd_table_temp;
	t_cmd	*cmd_table;

	i = 0;
	cmd_number_2 = cmd_number;
	cmd_table = get_core()->cmd_table;
	pipes_backup = STDIN_FILENO;
	
	while (cmd_number_2 > 0) // criação do fork
	{
		if (cmd_number_2 > 1)
			pipe(pipes);
		cmd_table[i].fork_pid = fork();
		if (cmd_table[i].fork_pid  == 0)
		{
			// cmd_table_temp = cmd_table[i];
			clear_child_exec(); // Free em tudo, exceto o index atual do cmd_table
			
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[1]);
			close(pipes[0]);

			dup2(pipes_backup, STDIN_FILENO);
			if (pipes_backup != 0)
				close(pipes_backup);
			
			exec_one_cmd(&cmd_table[i]);
			// free nas coisas
			
			exit(126); // tem o numero certo
		}
		if (pipes_backup != 0)
			close(pipes_backup);

		if (cmd_number_2 > 1)
		{
			pipes_backup = pipes[0];
			close(pipes[1]);
		}
		cmd_number_2--;
		i++;
	}

	i = 0;
	while (cmd_number > 0) // Loop para esperar todos os forks de cima
	{
		waitpid(cmd_table[i].fork_pid, &(get_core()->exit_status), 0);
		cmd_number--;
	}
}

void	fill_cmd_table(void)
{
	int		i;
	int		nb_of_cmds;
	t_cmd	*cmd_table;
	t_token	*ptr_temp;

	i = 0;
	nb_of_cmds = cmd_count();
	if (nb_of_cmds == 0)
		return ;
	
	get_core()->cmd_table = create_cmd_table();
	cmd_table = get_core()->cmd_table;
	if (cmd_table == NULL)
		return ;
	
	// Redirects ???
	ptr_temp = get_core()->token;
	
	while (i < nb_of_cmds)
	{
		cmd_table[i].cmd = ft_strdup(ptr_temp->str);
		cmd_table[i].args = cmd_to_matrix(&ptr_temp);
		cmd_table[i].envp = env_to_matrix();
		cmd_table[i].is_builtin = is_builtin(cmd_table[i].cmd);	
		i++;
	}
}

t_cmd	*create_cmd_table(void)
{
	t_cmd	*commands;
	int		nb_of_cmds;

	nb_of_cmds = cmd_count();
	get_core()->number_of_cmds_in_cmd_table = nb_of_cmds;
	commands = malloc(nb_of_cmds * sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	while (nb_of_cmds > 0)
	{
		commands[nb_of_cmds - 1].cmd = NULL;
		commands[nb_of_cmds - 1].args = NULL;
		commands[nb_of_cmds - 1].envp = NULL;
		commands[nb_of_cmds - 1].fork_pid = 0;
		commands[nb_of_cmds - 1].is_builtin = FALSE;
		t_redir_in	*redir_in;
		t_redir_out	*redir_out;
		nb_of_cmds--;
	}
	return(commands);
}

