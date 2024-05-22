/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:41:10 by dfrade            #+#    #+#             */
/*   Updated: 2024/05/22 17:41:41 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_has_path(char *cmd)
{
	int		i;

	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*build_path(char *cmd)
{
	int		i;
	char	*path_value;
	char	**split_path;
	char	*cmd_path;

	// Verifica se o comando já contém um caminho completo
	cmd_has_path(cmd);
	if (cmd_has_path(cmd) == 1)
		return (cmd);

	// Procura a variável de ambiente PATH
	path_value = my_get_env("PATH");

	// Separa os diretórios do PATH em um array de strings, salva em split_path e da free em path_value
	split_path = ft_split(path_value, ':');
	free (path_value);

	// Itera por cada diretório do PATH
	i = 0;
	while (split_path[i] != NULL)
	{
		// Aloca memória para o caminho completo de cada diretório (diretório + cmd + '/' + '/0')
		cmd_path = malloc((ft_strlen(split_path[i]) + ft_strlen(cmd) + 2) * sizeof(char));
		if (!cmd_path)
			return (NULL);

		// Constrói o caminho completo do diretório atual
		ft_strlcpy(cmd_path, split_path[i], ft_strlen(split_path[i]) + 1);
		ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], "/", 2);
		ft_strlcpy(&cmd_path[ft_strlen(cmd_path)], cmd, ft_strlen(cmd) + 1);

		// Verifica se o arquivo/diretório existe, se sim sai do while
		if (access(cmd_path, F_OK) == 0)
			break ;

		// Caminho ainda não encontrado pelo access, free no cmd_path e itera
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}

	// Libera os diretórios alocados com a split
	ft_free_matrice(split_path);
	free(cmd);

	// Retorna o caminho encontrado
	return (cmd_path);
}
