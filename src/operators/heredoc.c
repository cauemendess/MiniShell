/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:42:56 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/15 15:06:41 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(char *limiter);
void	wait_child_heredoc(pid_t pid);
void	prompt_heredoc(char *limiter);
char	*expand_on_heredoc(char *line);

void	capture_heredoc(void)
{
	char	*limiter;
	t_token	*cur;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	cur = get_core()->token;
	while (cur)
	{
		if (cur->token == HEREDOC && cur->next->token == WORD)
		{
			get_core()->doc_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			limiter = cur->next->str;
			if (get_core()->is_heredoc == FALSE)
				child_process(limiter);
		}
		cur = cur->next;
	}
}

void	child_process(char *limiter)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_heredoc);
		prompt_heredoc(limiter);
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
		if (exit_status != 0)
		{
			if (get_core()->exit_status != 130)
				get_core()->is_heredoc = TRUE;
			get_core()->exit_status = exit_status;
		}
		else
			get_core()->exit_status = 0;
	}
}

void	prompt_heredoc(char *limiter)
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
		else if (ft_strcmp(line, "$"))
			line = expand_on_heredoc(line);
		ft_putendl_fd(line, get_core()->doc_fd);
		free(line);
	}
	close(get_core()->doc_fd);
	clear_child();
}

char	*has_var(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			if (line[i + 1] == '?' || ft_isalnum(line[i + 1]))
				return (line + i);
		}
		i++;
	}
	return (NULL);
}

char	*search_var(char *str)
{
	int		i;
	char	*line;

	line = has_var(str);
	if (!line)
		return (NULL);
	i = 1;
	while (line[i] && (ft_isalnum(line[i])))
		i++;
	if (line[i] == '?')
		i++;
	return (ft_substr(line, 0, i));
}

char	*expand_on_heredoc(char *line)
{
	char	*var;

	while (has_var(line))
	{
		garbage_collect(var = search_var(line));
		line = ft_replace(line, var, my_get_env(var + 1));
	}
	return (line);
}
