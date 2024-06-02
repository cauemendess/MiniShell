/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:54:16 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/02 15:57:03 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token(t_token **list, t_token *target)
{
	t_token	*cur;

	cur = *list;
	while (cur)
	{
		if (cur == target)
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			else
				*list = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			free(cur->str);
			free(cur);
			break ;
		}
		cur = cur->next;
	}
}

void	clear_child(void)
{
	if (get_core()->token != NULL)
		clear_tkn_lst(&get_core()->token);
	if (get_core()->env_list)
		clear_env_lst(&get_core()->env_list);
	rl_clear_history();
	clear_garbage();
	close_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(get_core()->exit_status);
}

void	clear_child_exec(void)
{
	t_core	*core;

	core = get_core();
	clear_tkn_lst(&core->token);
	clear_env_lst(&core->env_list);
	clear_garbage();
	clear_cmd_table(core->cmd_table);
}

void	clear_cmd_table(t_cmd *cmd_table)
{
	int	i;

	i = 0;
	while (i < get_core()->cmd_table_len)
	{
		free(cmd_table[i].cmd);
		ft_free_matrice(cmd_table[i].args);
		ft_free_matrice(cmd_table[i].envp);
		i++;
	}
	free(cmd_table);
}

void	close_fds(void)
{
	size_t	index;

	index = 4;
	while (index <= 1024)
	{
		close(index);
		index++;
	}
}
