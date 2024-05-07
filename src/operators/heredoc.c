/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:42:56 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/07 16:32:10 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int doc_fd, char *limiter);
void	wait_child(pid_t pid);
void	prompt_heredoc(int doc_fd, char *limiter);


void	handle_heredoc(void)
{
	char	*limiter;
	t_token	*cur;
	int		doc_fd;

	cur = get_core()->token;
	while (cur)
	{
		if (cur->token == HEREDOC && cur->next->token == WORD)
		{
			doc_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			limiter = cur->next->str;
			if (get_core()->is_heredoc == FALSE)
				child_process(doc_fd, limiter);
		}
		cur = cur->next;
	}
}
void	child_process(int doc_fd, char *limiter)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		prompt_heredoc(doc_fd, limiter);
	else
		wait_child(pid);
}

void	wait_child(pid_t pid)
{
	int	wstatus;
	int	exit_status;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
	{
		exit_status = WEXITSTATUS(wstatus);
		if (exit_status == 130)
		{
			if (get_core()->exit_status != 130)
				get_core()->is_heredoc = TRUE;
			get_core()->exit_status = exit_status;
		}
		else
			get_core()->exit_status = 0;
	}
}

void	prompt_heredoc(int doc_fd, char *limiter)
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
		ft_putendl_fd(line, doc_fd);
		free(line);
	}
	clear_child();
	close(doc_fd);
}
