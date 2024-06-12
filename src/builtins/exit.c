/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:01 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/12 20:06:33 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_error(char *msg, char *argv);
int		is_valid_number(char **argv);

void	exit_shell(char **argv)
{
	long	number;
	
	number = 0;
	if (argv[0] != NULL && argv[1] == NULL)
		number = get_core()->exit_status;
	else if (argv[0] != NULL && argv[1] != NULL)
	{
		if (is_valid_number(argv) == 1)
		{
			number = ft_atoi(argv[1]);
			if (argv[2] != NULL)
			{
				print_exit_error("too many arguments\n", NULL);
				get_core()->exit_status = 2;
				return ;
			}
		}
		else
		{
			print_exit_error("numeric argument required\n", argv[1]);
			number = 2;
		}
	}
	clear_env_lst(&get_core()->env_list);
	if (get_core()->token)
		clear_tkn_lst(&get_core()->token);
	if(get_core()->cmd_table)
		clear_cmd_table(get_core()->cmd_table);
	unlink("heredoc_tmp");
	clear_garbage();
	exit(number);
}

int	is_valid_number(char **argv)
{
	int	i;

	i = 0;
	while (ft_isdigit(argv[1][i]) == 1)
		i++;
	if (argv[1][i] == '\0')
		return (1);
	else 
		return (0);
}

void	print_exit_error(char *msg, char *argv)
{
	char	*message;

	message = malloc((ft_strlen(msg) + ft_strlen(argv) + 8) * sizeof(char));
	if (message == NULL)
		return ;
	ft_strlcpy(message, "exit: ", 7);
	ft_strlcpy(&message[ft_strlen(message)], msg, ft_strlen(msg) + 1);
	ft_strlcpy(&message[ft_strlen(message)], argv, ft_strlen(argv) + 1);
	write(2, message, ft_strlen(message));
	free(message);
}
