/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielefrade <danielefrade@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:08:59 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/06 12:44:11 by danielefrad      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fluxo export:
// 1 - cmd export sem arg = imprimir list de env (com adaptação)
// 2 - se tem arg, validar nome da var(key)
//	   - while para key vai até '=' ou '\0'
//     - iniciar com alpha ou '_'
//     - restante alnum ou '-'
// 3 - verificar se a var já existe na lista de env (pq? para substituir e não recriar?)
// 4 - add a var (ou substituir a existente) com seus argumentos
// depois de tudo:
// ajustar a builtin env
// ajustar a env_to_matrix

void	print_export(t_env *var_list);
int		print_export_error(char *argv);

void	export(char **argv)
{
	t_env	*var_list;
	
	if (matrice_len(argv) == 1) //se digitou somente export
	{
        var_list = get_core()->env_list;
        print_export(var_list); // tenho que dar free???
	} 
    else // se digitou com args
    {
    	if(check_var_name(argv) == 0) // sintax de todas as keys deu certo
		{
			// verificar se a var já existe
			// add var + qq argumento na lista de env
		}
    }        
}

void	print_export(t_env *var_list)
{
	while (var_list)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(var_list->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putendl_fd(var_list->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		var_list = var_list->next;
	}
	get_core()->exit_status = 0;
}

int	check_var_name(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{ 
		if (ft_isalpha(argv[i][0]) == 1 || argv[i][0] == '_')
		{
			j = 0;
			while (argv[i][j] != '=' || argv[i][j] != '\0')
			{
				if (ft_isalnum(argv[i][j]) == 1 || argv[i][j] == '_')
					j++;
				else
					return(print_export_error(argv[i]));
			}
			i++;
		}
		else
			return (print_export_error(argv[i]));
	}
	return (0);
}

int	print_export_error(char *argv)
{
	ft_printf("export: `%s': not a valid identifier", argv);
	get_core()->exit_status = 1;
	return (1);
}
