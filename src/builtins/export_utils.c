/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:46:49 by dfrade            #+#    #+#             */
/*   Updated: 2024/06/08 11:49:04 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var_value(t_env *var, char *str)
{
	free(var->value);
	var->value = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(var->value, str, ft_strlen(str) + 1);
}

void	add_new_var(char *key, char *value)
{
	t_env	*new_var;

	if (*value != '\0' || *(value - 1) == '\0')
		new_var = create_env_lst(key, value);
	else
		new_var = create_env_lst(key, NULL);
	add_env(&(get_core()->env_list), new_var);
}

void	print_export_error(char *argv)
{
	char	*message;

	message = malloc((ft_strlen(argv) + 35 + 1) * sizeof(char));
	if (message == NULL)
		return ;
	ft_strlcpy(message, "export: `", 10);
	ft_strlcpy(&message[ft_strlen(message)], argv, ft_strlen(argv) + 1);
	ft_strlcpy(&message[ft_strlen(message)], "': not a valid identifier\n", 29);
	write(2, message, ft_strlen(message));
	free(message);
	get_core()->exit_status = 1;
}
