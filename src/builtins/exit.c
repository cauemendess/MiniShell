/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:01 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/07 16:23:47 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	if (get_core()->input)
		free(get_core()->input);
	clear_env_lst(&get_core()->env_list);
	if (get_core()->token)
		clear_tkn_lst(&get_core()->token);
	unlink("heredoc_tmp");
	clear_garbage();
	exit(get_core()->exit_status);
}
