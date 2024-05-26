/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielefrade <danielefrade@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/26 18:31:27 by danielefrad      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	handle_cmd_number();
void	exec_one_cmd(t_token *cmd);
t_bool	is_builtin(t_token *cmd);
char	*build_path(char *cmd);
int		cmd_has_path(char *cmd);
char	**cmd_to_matrix(t_token *cmd);
char	**env_to_matrix(void);
int		cmd_count();

// void	cmd_parse(void)
// {
// 	t_token	*list;
// 	list = get_core()->token;
// }

void handle_cmd_number() // decidir qual função chamar de acordo com o nb de comandos
{
	int cmd_number;

	cmd_number = cmd_count();
	if (cmd_number == 0)
		clear_garbage(); // escolher a função correta para free em tudo até aqui
	else if (cmd_number == 1)
		exec_one_cmd(get_core()->token);
	else if (cmd_number > 1)
		exec_mult_cmd(cmd_number);
	//free nas coisas que tem que dar free
}

void	exec_mult_cmd(int cmd_nb)
{
	int *fork_return;
	int cmd_number;
	int	i;
	t_token *token;
	t_token *cmd;
	int	pipes[2];
	int	pipes_backup;
	
	cmd_number = cmd_nb;
	// Mallocar espaço para guardar a resposta de todos os forks
	fork_return = malloc((cmd_number) * sizeof (int));
	if (fork_return == NULL)
	{
		ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
		return ;
	}
	
	// Loop para criação do fork
	i = 0;
	token = get_core()->token;
	pipes_backup = STDIN_FILENO;
	while (cmd_number > 0)
	{
		if (cmd_number > 1)
			// Abrir pipe (Quando necessário)
			pipe(pipes);
				// verificar erro depois

		// Fork
		fork_return[i] = fork();
		if (fork_return[i] == 0)
		{
			cmd = NULL;
			 
			// Criar lista de tokens para 1 único comando
			while (token != NULL && token->token != (int)PIPE)
			{
				add_token(&cmd, create_tkn_lst(token->str, token->token));
				token = token->next;
			}

			if (cmd_number > 1)
			{
				// int dup2(int quero_dup, int quero_apagar)
				dup2(pipes[1], STDOUT_FILENO);
				close(pipes[1]);
				close(pipes[0]);
			}

			dup2(pipes_backup, STDIN_FILENO);
			if (pipes_backup != 0) // nunca fecha a entrada padrão
				close(pipes_backup);
			
			// copia 1 comando pra variável cmd
			exec_one_cmd(cmd);
			// free nas coisas
			exit(126); // tem o numero certo, aqui o exit, como em todos, é um tratamento de erro, pois o execve já mata a criança caso dê certo
		}
		if (pipes_backup != 0) // nunca fecha a entrada padrão
			close(pipes_backup);
		// backup do pipe
		if (cmd_number > 1)
		{
			pipes_backup = pipes[0];
			close(pipes[1]);
		}

		// incrementa (próx. cmd), pq o que acontece na criança não altera ou reflete no pai
		while (token != NULL && token->token != (int)PIPE)
		{
			token = token->next; // passando uma palavra de cada vez
		}
		if (token != NULL) // garanto que estou no próximo comando, pulando o pipe
			token = token->next;
		
		cmd_number--;
		i++;
	}
	
	// Loop para esperar todos os forks de cima
	i = 0;
	while (cmd_nb > 0)
	{
		// Esperar TODOS os pids (retorno do fork) na ordem que executamos (waitpid)
		waitpid(fork_return[i], &(get_core()->exit_status), 0);
		cmd_nb--;
	}
}

void exec_one_cmd(t_token *cmd)
{
	// execução de redirect
	// expansão de variáveis
	char	**cmd_matrix;
	char	**env_matrix;
	int		fork_return;

	if (is_builtin(cmd))
	{
		// chama a função de builtin de acordo com a builtin (talvez pode ser um ponteiro direto para a função, mas aqui o prototipo tem que ser igual)	
	}
	else
	{	
		fork_return = fork();
		if (fork_return == 0)
		{
			// se o retorno da função está ok
			cmd_matrix = cmd_to_matrix(cmd);
			if (cmd_matrix == NULL)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			
			cmd_matrix[0] = build_path(cmd_matrix[0]);
			
			// se encontrei o comando
			if (cmd_matrix[0] == NULL)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			
			// se é diretório
			struct stat	path_status; //já tem no sistema, só importar a lib utilizar 
			stat(cmd_matrix[0], &path_status);
			if (S_ISDIR(path_status.st_mode) != 0)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
		
			// se posso executar
			if (access(cmd_matrix[0], X_OK) != 0)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			
			// se o retorno da função está ok
			env_matrix = env_to_matrix();
			if (env_matrix == NULL)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			execve(cmd_matrix[0], cmd_matrix, env_matrix);
			// free em tudo
			exit(126); // tem o numero certo, aqui o exit, como em todos, é um tratamento de erro, pois o execve já mata a criança caso dê certo
		}
		wait(&get_core()->exit_status);
	}
}

t_bool is_builtin(t_token *cmd)
{
	int	i;
	const char *builtins[] = {"echo", "exit", "pwd", "unset", "export", "env", "cd", NULL};
	
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd->str, builtins[i], ft_strlen(cmd->str)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	**cmd_to_matrix(t_token *cmd)
{
	t_token	*temp_count;
	char	**matrix;
	int		lenght;
	int		i;

	temp_count = cmd; // ou poderia fazer fora daqui
	while (temp_count != NULL) // contar quantos tokens
	{
		temp_count = temp_count->next;
		lenght++;
	}
	
	matrix = malloc((lenght + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	
	i = 0;
	while (cmd != NULL)
	{
		matrix[i] = ft_strdup(cmd->str);
		if (matrix[i] == NULL)
		{
			// Free em tudo	
			return (NULL);
		}
		cmd = cmd->next;
		i++;
	}
	matrix[i] = NULL;	
	return (matrix);
}

char	**env_to_matrix(void)
{
	char	**env_matrix;
	t_env	*env_list;
	t_env	*temp_count;
	int		lenght;
	int		i;
	
	
	env_list = get_core()->env_list;
	if (env_list == NULL)
		return (NULL);
	
	temp_count = env_list;
	lenght = 0;
	while (temp_count != NULL)
	{
		lenght++;
		temp_count = temp_count->next;
	}

	env_matrix = malloc((lenght + 1) * sizeof(char *));
	if (env_matrix == NULL)
		return (NULL);
	
	i = 0;
	while (env_list != NULL)
	{
		// mallocar
		env_matrix[i] = malloc((ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2) * sizeof(char *));
		if (env_matrix[i] == NULL)
		{
			// free em tudo
			return (NULL);		
		}
		// copiar
		ft_strlcpy(env_matrix[i], env_list->key, ft_strlen(env_list->key) + 1);
		ft_strlcpy(env_matrix[i], "=", 2);
		ft_strlcpy(env_matrix[i], env_list->value, ft_strlen(env_list->value) + 1);
	
		env_list = env_list->next;
		i++;
	}
	env_matrix[i] = NULL;
	return(env_matrix);	
}

int	cmd_count() // contar o número de comandos 
{
	t_token	*list;
	int 	i;
	
	list = get_core()->token;
	if (list == NULL)
		return (0);
	i = 1;
	while (list != NULL)
	{
		if (list->token == (int)PIPE)
			i++;
		list = list->next;
	}
	return (i);
}

// INFO:
// - o numero de comandos é pipe + 1 (posso usar para malloc?)
// - os comandos vão para o execve com os argumentos
// - cmd da build_path é o core->token->str
// - tipos não mudam, o que muda é a estrutura (posso ter um array ou um struct ou uma lista com tipos char, int etc...)
// - strlcpy por padrão copia size -1, por sempre passar size + 1