/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/02 12:42:10 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_table(void)
{
	t_cmd	*commands;
	int		nb_of_cmds;

	nb_of_cmds = cmd_count();
	if (nb_of_cmds == 0)
		return (NULL);
	get_core()->cmd_table_len = nb_of_cmds;
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
		// t_redir_in	*redir_in;
		// t_redir_out	*redir_out;
		nb_of_cmds--;
	}
	return(commands);
}

void	fill_cmd_table(void)
{
	t_cmd	*cmd_table;
	t_token	*ptr_temp;
	int		nb_of_cmds;
	int		i;

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
t_bool is_builtin(char *cmd)
{
	int	i;
	const char *builtins[] = {"echo", "exit", "pwd", "unset", "export", "env", "cd", NULL};
	
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	cmd_count(void)
{
	t_token	*list;
	int		i;
	
	list = get_core()->token;
	if (list == NULL)
		return (0);
	i = 1;
	while (list != NULL)
	{
		if (list->token == (int)PIPE)
			i++;
		list = list->next;
	}
	return (i);
}