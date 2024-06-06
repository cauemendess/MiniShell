/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:59 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/06 20:45:01 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *var_list);
void	check_and_insert_vars(char **argv);
t_env	*get_node_with_key_equal_to(char *argv);
void	print_export_error(char *argv);

void	export(char **argv)
{
	t_env	*var_list;

	if (matrice_len(argv) == 1)
	{
        var_list = get_core()->env_list;
        print_export(var_list);
	} 
    else
		check_and_insert_vars(argv);
}

void	print_export(t_env *var_list)
{
	while (var_list)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(var_list->key, STDOUT_FILENO);
		if (var_list->value != NULL)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(var_list->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		var_list = var_list->next;
	}
	get_core()->exit_status = 0;
}

void	check_and_insert_vars(char **argv)
{
	t_env	*var;
	t_env	*node;
	char	*str;
	int		i;
	int		j;

	i = 1;
	str = argv[i];
	while (str != NULL)
	{ 
		if (ft_isalpha(str[0]) == 1 || str[0] == '_')
		{
			j = 0;
			while (str[j] != '=' && str[j] != '\0')
			{
				if (ft_isalnum(str[j]) == 1 || str[j] == '_')
					j++;
				else
				{
					print_export_error(str);
					break ;
				}
			}
			if (str[j] == '=' || str[j] == '\0') // Nome da variável é correto
			{
				if (str[j] == '=')
				{
					str[j] = '\0';
					j++;
				}
				var = get_node_with_key_equal_to(str);
				if (var != NULL)
				{
					if (str[j] != '\0' || str[j - 1] == '\0')
					{
						free(var->value);
						var->value = malloc((ft_strlen(&str[j]) + 1) * sizeof(char));
						ft_strlcpy(var->value, &str[j], ft_strlen(&str[j]) + 1);
					}
				}
				else
				{
					if (str[j] != '\0' || str[j - 1] == '\0')
						node = create_env_lst(str, &str[j]);
					else
						node = create_env_lst(str, NULL);
					add_env(&(get_core()->env_list), node);
				}
			}	
		}
		else
			print_export_error(str);
		i++;
		str = argv[i];
	}
}

t_env	*get_node_with_key_equal_to(char *argv)
{
	t_env	*env;

	env = get_core()->env_list;
	while (env)
	{
		if(ft_strncmp(argv, env->key, ft_strlen(env->key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_export_error(char *argv)
{
	ft_printf("export: `%s': not a valid identifier", argv);
	get_core()->exit_status = 1;
}