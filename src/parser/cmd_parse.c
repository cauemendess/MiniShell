/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 19:13:31 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd_table(void)
{
	t_cmd	*commands;
	int		nb_of_cmds;
	int		i;

	i = 0;
	nb_of_cmds = cmd_count();
	if (nb_of_cmds == 0)
		return (NULL);
	get_core()->cmd_table_len = nb_of_cmds;
	commands = malloc(nb_of_cmds * sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	while (i < nb_of_cmds)
	{
		commands[i].cmd = NULL;
		commands[i].args = NULL;
		commands[i].envp = NULL;
		commands[i].redir_in = NULL;
		commands[i].redir_out = NULL;
		commands[i].fork_pid = 0;
		commands[i].index = i;
		commands[i].is_builtin = FALSE;
		i++;
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
	get_core()->cmd_table = create_cmd_table();
	cmd_table = get_core()->cmd_table;
	if (cmd_table == NULL || nb_of_cmds == 0)
		return ;
	ptr_temp = get_core()->token;
	while (++i < nb_of_cmds)
	{
		ptr_temp = handle_redirects(&cmd_table[i], ptr_temp, i);
		save_last_redir_in(&cmd_table[i].redir_in);
		save_last_redir_out(&cmd_table[i].redir_out);
		if (get_core()->error.file_error[i])
			get_core()->error.cmd_error[i] = TRUE;
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
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0
			&& cmd[ft_strlen(builtins[i])] == '\0')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	malloc_len(char *key, char *value)
{
	return ((ft_strlen(key) + ft_strlen(value) + 2) * sizeof(char *));
}
