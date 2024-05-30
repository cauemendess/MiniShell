/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:32:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/30 16:20:43 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int matrice_len(char **matrice)
{
	int i;

	i = 0;
	while (matrice[i])
		i++;
	return (i);
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
t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

int	main(void)
{
	t_core	*core;
	core = get_core();
	core->invalid = -1;
	get_env_vars(core);
	prompt_loop();
	return (core->exit_status);
}
