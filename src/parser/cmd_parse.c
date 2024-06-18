/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/17 21:02:21 by dfrade           ###   ########.fr       */
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
		commands[nb_of_cmds - 1].redir_in = NULL;
		commands[nb_of_cmds - 1].redir_out = NULL;
		commands[nb_of_cmds - 1].fork_pid = 0;
		commands[nb_of_cmds - 1].is_builtin = FALSE;
		nb_of_cmds--;
	}
	return (commands);
}

void	fill_cmd_table(void)
{
	t_cmd	*cmd_table;
	t_token	*ptr_temp;
	int		nb_of_cmds;
	int		i;

	i = -1;
	nb_of_cmds = cmd_count();
	if (nb_of_cmds == 0)
		return ;
	get_core()->cmd_table = create_cmd_table();
	cmd_table = get_core()->cmd_table;
	if (cmd_table == NULL)
		return ;
	ptr_temp = get_core()->token;
	while (++i < nb_of_cmds)
	{
		ptr_temp = handle_redirects(&cmd_table[i], ptr_temp);
		save_last_redir_in(&cmd_table[i].redir_in);
		save_last_redir_out(&cmd_table[i].redir_out);
		if (ptr_temp != NULL && ptr_temp->token != (int)PIPE
			&& ptr_temp->token != (int)END)
			filling_with_value(&cmd_table[i], &ptr_temp);
		else if (ptr_temp->token == (int)(PIPE))
			ptr_temp = ptr_temp->next;
	}
}

void	filling_with_value(t_cmd *cmd_table, t_token **ptr_temp)
{
	cmd_table->cmd = ft_strdup((*ptr_temp)->str);
	cmd_table->args = cmd_to_matrix(ptr_temp);
	cmd_table->envp = env_to_matrix();
	cmd_table->is_builtin = is_builtin(cmd_table->cmd);
}

t_bool	is_builtin(char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"echo", "exit", "pwd", "unset", "export", "env", "cd", NULL};

	i = 0;
	if (cmd[i] == '\0')
		return (FALSE);
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	malloc_len(char *key, char *value)
{
	return ((ft_strlen(key) + ft_strlen(value) + 2) * sizeof(char *));
}
