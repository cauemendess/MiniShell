/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:54 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/08 12:42:50 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var(char *key, char *value)
{
	t_env	*var;

	var = get_core()->env_list;
	while (var)
	{
		if (ft_strcmp(var->key, key) == 0)
		{
			var->value = ft_replace(var->value, var->value, value);
			return ;
		}
		var = var->next;
	}
}

void	cd_error_process(char *cur)
{
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(cur);
	get_core()->exit_status = 2;
}

void	cd(char **argv)
{
	char	*new_path;
	char	*old_path;

	get_core()->exit_status = 0;
	if (matrice_len(argv) > 2)
	{
		error("cd: too many arguments", 1, 2);
		return ;
	}
	if (matrice_len(argv) == 1 || argv[1][0] == '~')
		garbage_collect(new_path = my_get_env("HOME"));
	else
		garbage_collect(new_path = ft_strdup(argv[1]));
	old_path = getcwd(NULL, 0);
	if (!new_path)
	{
		error("cd: HOME not set", 1, 2);
		free(old_path);
		return ;
	}
	if (chdir(new_path) == -1)
		cd_error_process(old_path);
	else
	{
		set_var("OLDPWD", old_path);
		set_var("PWD", getcwd(NULL, 0));
	}
}
