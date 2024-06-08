/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:59 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/07 22:24:17 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *var_list);
void	check_and_insert_vars(char **argv);
t_env	*get_node_with_key_equal_to(char *argv);
void	print_export_error(char *argv);

char	*valid_sintax_key_and_value_position(char *str);
void	replace_var_value(t_env *var, char *str);
void	add_new_var(char *key, char *value);



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
	char	*str_key;
	char	*str_value;
	int		i;

	i = 1;
	str_key = argv[i];
	while (str_key != NULL)
	{
		str_value = valid_sintax_key_and_value_position(str_key);
		if (*str_value == '=' || *str_value == '\0')
		{
			if (*str_value == '=')
			{
				*str_value = '\0';
				str_value = str_value + 1;
			}
			var = get_node_with_key_equal_to(str_key);
			if ((var != NULL) && (*str_value != '\0' || str_value[0 - 1] == '\0'))
				replace_var_value(var, str_value);
			else
				add_new_var(str_key, str_value);
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
		if(ft_strncmp(argv, env->key, ft_strlen(env->key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_export_error(char *argv)
{
	char	*message;
	
	message = malloc((ft_strlen(argv) + 35 + 1) * sizeof(char));
	if(message == NULL)
		return ;
	ft_strlcpy(message, "export: `", 10);
	ft_strlcpy(&message[ft_strlen(message)], argv, ft_strlen(argv) + 1);
	ft_strlcpy(&message[ft_strlen(message)], "': not a valid identifier\n", 29);
	write(2, message, ft_strlen(message));
	free(message);
	get_core()->exit_status = 1;
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

void	replace_var_value(t_env *var, char *str)
{
	free(var->value);
	var->value = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(var->value, str, ft_strlen(str) + 1);
}

void	add_new_var(char *key, char *value)
{
	t_env *new_var;
	
	if (*value != '\0' || *(value - 1) == '\0')
		new_var = create_env_lst(key, value);
	else
		new_var = create_env_lst(key, NULL);
	add_env(&(get_core()->env_list), new_var);
}