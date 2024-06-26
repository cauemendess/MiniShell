/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:42:56 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 16:54:43 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(char *limiter, t_bool flag);
void	wait_child_heredoc(pid_t pid);
void	prompt_heredoc(char *limiter, t_bool flag);
char	*expand_on_heredoc(char *line);


t_bool	has_quote(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '"' || str[i] == '\'')
			return(TRUE);
		i++;
	}
	return(FALSE);
}

void	capture_heredoc(void)
{
	char	*limiter;
	t_token	*cur;
	t_bool	flag;

	flag = FALSE;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cur = get_core()->token;
	while (cur)
	{
		if (cur->token == HEREDOC && cur->next->token == WORD)
		{
			if(has_quote(cur->next->str))
			{
				flag = TRUE;
				remove_quote(cur->next->str, cur);
			}
			get_core()->doc_fd = open("heredoc_tmp",
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			limiter = cur->next->str;
			if (get_core()->is_heredoc == FALSE)
				child_process(limiter, flag);
		}
		cur = cur->next;
	}
}

void	child_process(char *limiter, t_bool flag)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_heredoc);
		prompt_heredoc(limiter, flag);
	}
	else
		wait_child_heredoc(pid);
	close(get_core()->doc_fd);
}

void	wait_child_heredoc(pid_t pid)
{
	int	wstatus;
	int	exit_status;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		exit_status = WEXITSTATUS(wstatus);
		if (exit_status == 130)
		{
			if (get_core()->exit_status == 130)
				get_core()->is_heredoc = TRUE;
			get_core()->exit_status = exit_status;
		}
		else
			get_core()->exit_status = 0;
	}
}

void	prompt_heredoc(char *limiter, t_bool flag)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		else if (flag == FALSE && ft_strcmp(line, "$"))
			line = expand_on_heredoc(line);
		ft_putendl_fd(line, get_core()->doc_fd);
		free(line);
	}
	close(get_core()->doc_fd);
	clear_child();
}
