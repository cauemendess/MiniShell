/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:34:35 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/16 01:16:53 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *msg, int status, int fd)
{
	ft_putendl_fd(msg, fd);
	get_core()->exit_status = status;
}

char	*get_error_message(char token)
{
	if (token == '&')
		return ("syntax error: near unexpected token `&`");
	else if (token == '\\')
		return ("syntax error: near unexpected token `\\`");
	else if (token == ';')
		return ("syntax error: near unexpected token `;`");
	else
		return (NULL);
}

t_bool	only_spaces(void)
{
	unsigned long	i;
	char			*line;

	line = get_core()->input;
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	matrice_len(char **matrice)
{
	int	i;

	i = 0;
	while (matrice[i])
		i++;
	return (i);
}
