/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:07:01 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/16 02:26:21 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid_number(char **argv);
void	print_exit_error(char *msg, char *argv);
void	clear_exit_shell(int status);

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
				get_core()->exit_status = 1;
				return ;
			}
		}
		else
		{
			print_exit_error("numeric argument required\n", argv[1]);
			number = 2;
		}
	}
	clear_exit_shell(number);
}

int	is_valid_number(char **argv)
{
	int	i;

	i = 0;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	if (argv[1][i] == '\0')
		return (0);
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

void	clear_exit_shell(int status)
{
	clear_env_lst(&get_core()->env_list);
	if (get_core()->token)
		clear_tkn_lst(&get_core()->token);
	if (get_core()->cmd_table)
		clear_cmd_table(get_core()->cmd_table);
	unlink("heredoc_tmp");
	clear_garbage();
	exit(status);
}
