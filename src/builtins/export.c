/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:59 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/16 01:35:31 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char **argv, int fd)
{
	t_env	*var_list;

	if (matrice_len(argv) == 1)
	{
		var_list = get_core()->env_list;
		print_export(var_list, fd);
	}
	else
		check_and_insert_vars(argv);
}

void	check_and_insert_vars(char **argv)
{
	t_env	*var;
	char	*str_key;
	char	*str_val;
	int		i;

	i = 1;
	str_key = argv[i];
	while (str_key != NULL)
	{
		str_val = valid_sintax_key_and_value_position(str_key);
		if (*str_val == '=' || *str_val == '\0')
		{
			if (*str_val == '=')
			{
				*str_val = '\0';
				str_val = str_val + 1;
			}
			var = get_node_with_key_equal_to(str_key);
			if ((var != NULL) && (*str_val != '\0' || str_val[0 - 1] == '\0'))
				replace_var_value(var, str_val);
			else
				add_new_var(str_key, str_val);
		}
		str_key = argv[++i];
	}
}

t_env	*get_node_with_key_equal_to(char *argv)
{
	t_env	*env;

	env = get_core()->env_list;
	while (env)
	{
		if (ft_strncmp(argv, env->key, ft_strlen(env->key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*valid_sintax_key_and_value_position(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '\0' && (ft_isalpha(str[0]) == 1 || str[0] == '_'))
	{
		while (str[i] != '=' && str[i] != '\0')
		{
			if (ft_isalnum(str[i]) == 1 || str[i] == '_')
				i++;
			else
			{
				print_export_error(str);
				break ;
			}
		}
	}
	else
		print_export_error(str);
	return (&str[i]);
}

void	print_export(t_env *var_list, int fd)
{
	while (var_list)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var_list->key, fd);
		if (var_list->value != NULL)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(var_list->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		var_list = var_list->next;
	}
	get_core()->exit_status = 0;
}
