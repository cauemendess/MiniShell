/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrade <dfrade@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:32:03 by csilva-m          #+#    #+#             */
/*   Updated: 2024/05/31 18:22:51 by dfrade           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	handle_cmd_number(void);
void	exec_one_cmd(t_cmd *cmd_table);
void	exec_mult_cmd(int cmd_number);
t_bool	is_builtin(char *cmd);
char	*build_path(char *cmd);
int		cmd_has_path(char *cmd);
char	**cmd_to_matrix(t_token **ptr_token);
char	**env_to_matrix(void);
int		cmd_count(void);
void	clear_child(void);
void	fill_cmd_table(void);
t_cmd	*create_cmd_table(void);


void handle_cmd_number(void) // decidir qual função chamar de acordo com o nb de comandos
{
	int cmd_number;

	cmd_number = cmd_count();
	if (cmd_number == 0)
		clear_garbage(); // escolher a função correta para free em tudo até aqui
	else if (cmd_number == 1)
		exec_one_cmd(get_core()->cmd_table);
	else if (cmd_number > 1)
		exec_mult_cmd(cmd_number);
	//free nas coisas que tem que dar free
}

void exec_one_cmd(t_cmd *cmd_table)
{
	int fork_pid;
	
	if (cmd_table->is_builtin == TRUE)
	{
		// chama a função de builtin de acordo com a builtin (talvez pode ser um ponteiro direto para a função, mas aqui o prototipo tem que ser igual)	
	}
	else
	{	
		fork_pid = fork();
		if (cmd_table->fork_pid == 0)
		{
			// execução de redirect (Trocar os fd pros redirects, se for necessário)


			// se o retorno da função está ok
			cmd_table->cmd = build_path(cmd_table->cmd);
			
			// se encontrei o comando
			if (cmd_table->cmd == NULL)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			
			// se é diretório
			struct stat	cmd_is_dir; //já tem no sistema, só importar a lib utilizar 
			stat(cmd_table->cmd, &cmd_is_dir); // preencher a struct
			if (S_ISDIR(cmd_is_dir.st_mode) != 0) // saber se é diretório ou não
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
		
			// se posso executar
			if (access(cmd_table->cmd, X_OK) != 0)
			{
				ft_printf("%s\n", "Mensagem de erro de acordo com o erro específico");
				exit(1); // tem que dar o número certo do erro
			}
			
			execve(cmd_table->cmd, cmd_table->args, cmd_table->envp);
			// free em tudo
			exit(126); // tem o numero certo
		}
		wait(&get_core()->exit_status);
	}
}

void	exec_mult_cmd(int cmd_number)
{
	int		i;
	int		cmd_number_2;
	int		pipes[2];
	int		pipes_backup;
	t_cmd	*cmd_table_temp;
	t_cmd	*cmd_table;

	// Loop para criação do fork
	i = 0;
	cmd_number_2 = cmd_number;
	cmd_table = get_core()->cmd_table;
	pipes_backup = STDIN_FILENO;
	
	while (cmd_number_2 > 0)
	{
		if (cmd_number_2 > 1)
			pipe(pipes); // Abrir pipe (Quando necessário), verificar erro depois
		cmd_table[i].fork_pid = fork(); // Fork
		if (cmd_table[i].fork_pid  == 0)
		{
			cmd_table_temp = cmd_table[i];
			clear_child(); // Free em tudo, exceto o index atual do cmd_table
			
			// int dup2(int quero_dup, int quero_apagar)
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[1]);
			close(pipes[0]);

			dup2(pipes_backup, STDIN_FILENO);
			if (pipes_backup != 0) // nunca fecha a entrada padrão
				close(pipes_backup);
			
			exec_one_cmd(&cmd_table[i]);
			// free nas coisas
			exit(126); // tem o numero certo
		}
		if (pipes_backup != 0) // nunca fecha a entrada padrão
			close(pipes_backup);

		if (cmd_number_2 > 1) // backup do pipe
		{
			pipes_backup = pipes[0];
			close(pipes[1]);
		}
		cmd_number_2--;
		i++;
	}
	
	// Loop para esperar todos os forks de cima
	i = 0;
	while (cmd_number > 0)
	{
		// Esperar TODOS os pids (retorno do fork) na ordem que executamos (waitpid)
		waitpid(cmd_table[i].fork_pid, &(get_core()->exit_status), 0);
		cmd_number--;
	}
}

t_bool is_builtin(char *cmd)
{
	int	i;
	const char *builtins[] = {"echo", "exit", "pwd", "unset", "export", "env", "cd", NULL};
	
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	**cmd_to_matrix(t_token **ptr_token)
{
	t_token	*ptr_token_list;
	char	**matrix;
	int		lenght;
	int		i;

	ptr_token_list = *ptr_token;
	while (ptr_token_list != NULL && ptr_token_list->token != (int)PIPE) // contar quantos tokens
	{
		ptr_token_list = ptr_token_list->next;
		lenght++;
	}
	
	matrix = malloc((lenght + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	
	i = 0;
	ptr_token_list = *ptr_token;
	while (ptr_token_list != NULL && ptr_token_list->token != (int)PIPE)
	{
		matrix[i] = ft_strdup(ptr_token_list->str);
		if (matrix[i] == NULL)
		{
			ft_free_matrice(matrix);
			return (NULL);
		}
		ptr_token_list = ptr_token_list->next;
		i++;
	}
	*ptr_token = ptr_token_list;
	if ((*ptr_token)->token == (int)PIPE)
		*ptr_token = (*ptr_token)->next;
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

int	cmd_count(void) // contar o número de comandos 
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

void	fill_cmd_table(void)
{
	int		i;
	int		nb_of_cmds;
	t_cmd	*cmd_table;
	t_token	*ptr_temp;

	i = 0;
	nb_of_cmds = cmd_count();
	if (nb_of_cmds == 0)
		return ;
	
	get_core()->cmd_table = create_cmd_table(); // inicializa todos os cmd_table que existe com valores padrões e salva no array cmd_table
	cmd_table = get_core()->cmd_table; // passa o endereço da cmd_table para a var criada localmente
	if (cmd_table == NULL)
		return ;
	
	// Redirects é com o Cauê
	ptr_temp = get_core()->token;
	
	while (i < nb_of_cmds)
	{
		cmd_table[i].cmd = ft_strdup(ptr_temp->str);
		cmd_table[i].args = cmd_to_matrix(&ptr_temp);
		cmd_table[i].envp = env_to_matrix();
		cmd_table[i].is_builtin = is_builtin(cmd_table[i].cmd);	
		i++;
	}
}

t_cmd	*create_cmd_table(void)
{
	t_cmd	*commands;
	int		nb_of_cmds;

	nb_of_cmds = cmd_count();
	commands = malloc(nb_of_cmds * sizeof(t_cmd));
	if (commands == NULL)
		return (NULL);
	while (nb_of_cmds > 0)
	{
		commands[nb_of_cmds - 1].cmd = NULL;
		commands[nb_of_cmds - 1].args = NULL;
		commands[nb_of_cmds - 1].envp = NULL;
		commands[nb_of_cmds - 1].fork_pid = 0;
		commands[nb_of_cmds - 1].is_builtin = FALSE;
		// t_redir_in	*redir_in;
		// t_redir_out	*redir_out;
		// t_proc		process_location; talvez use ou não
		nb_of_cmds--;
	}
	return(commands);
}

void	clear_child(void)
{
	t_core	*core;
	
	core = get_core();

	free(core->input); // char *input
	clear_tkn_lst(core->token);	// t_token *token;	
	clear_env_lst(core->env_list); // t_env *env_list;
	ft_free_matrice(core->env);	// char **env
	clear_garbage();// t_list *garbage
	free(core->cmd_table); // t_cmd *cmd_table
}

// INFO:
// - o numero de comandos é pipe + 1 (posso usar para malloc?)
// - os comandos vão para o execve com os argumentos
// - cmd da build_path é o core->token->str
// - tipos não mudam, o que muda é a estrutura (posso ter um array ou um struct ou uma lista com tipos char, int etc...)
// - strlcpy por padrão copia size -1, por sempre passar size + 1
// - exit (nb) tem o numero certo, aqui o exit, como em todos, é um tratamento de erro, pois o execve já mata a criança caso dê certo