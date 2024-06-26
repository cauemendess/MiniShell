/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/06/26 17:41:03 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termio.h>
# include <unistd.h>

typedef enum e_type
{
	WORD = 1,
	REDIRECT,
	APPEND,
	PIPE,
	HEREDOC,
	SPACES,
	VAR,
	TRUNC,
	END
}						t_type;

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef struct s_error
{
	t_bool				file_error[4096];
	t_bool				cmd_error[4096];
}						t_error;

typedef struct s_token
{
	char				*str;
	int					token;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*prev;
	struct s_env		*next;

}						t_env;

typedef struct s_redir_in
{
	char				*file_name;
	int					fd;
	t_type				tkn_type;
	struct s_redir_in	*next;
}						t_redir_in;

typedef struct s_redir_out
{
	char				*file_name;
	int					fd;
	t_type				tkn_type;
	struct s_redir_out	*next;
}						t_redir_out;

typedef struct s_cmd
{
	int					fork_pid;
	int					index;
	char				*cmd;
	char				**args;
	char				**envp;
	t_bool				is_builtin;
	t_redir_in			*redir_in;
	t_redir_out			*redir_out;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_core
{
	char				*input;
	t_token				*token;
	t_env				*env_list;
	t_cmd				*cmd;
	char				**env;
	t_list				*garbage;
	t_bool				is_heredoc;
	int					exit_status;
	char				invalid;
	t_cmd				*cmd_table;
	int					cmd_table_len;
	int					doc_fd;
	t_error				error;
}						t_core;

// core
t_core					*get_core(void);
void					prompt_loop(void);
void					process(void);
void					error(char *msg, int status, int fd);
void					file_error(char *file_name, char *str, int status,
							int index);
void					file_error_ambiguous(char *str, int status, int index);
t_env					*create_env_lst(char *key, char *value);
void					add_env(t_env **env, t_env *new);
void					save_tty(int tty_fd);

// syntax errors
t_bool					syntax_errors(void);
t_bool					only_spaces(void);
t_bool					check_start_pipe(void);
t_bool					check_op_op(void);
t_bool					check_end_op(void);
t_bool					forbiden_token(void);
t_bool					check_close_quotes(void);
char					*get_error_message(char token);
void					split_quotes(char *str, int *i);
int						ft_quotes_status(char c, int status);
void					remove_expansions_to_nothing(void);
void					remove_quote(char *str, t_token *cur);

// env list
t_env					*create_env_lst(char *key, char *value);
void					add_env(t_env **env, t_env *new);
void					split_env_vars(void);
void					get_env_vars(t_core *core);

// tokenizer
t_token					*create_tkn_lst(char *str, int type);
void					add_token(t_token **token, t_token *new);
void					save_words(char *input, int start, int end);
void					save_separator(char *input, int pos, int type);
int						check_token(char *str);
void					lexing(char *input);
t_bool					tokenizer(char *input);

// parser
char					*find_var(char *str, int j);
char					*my_get_env(char *key);
void					parsing_vars(void);
t_bool					have_dollar(char *str, int *i, int *status);
t_bool					mult_dollar(char *str, char **var);
void					replace_invalid(t_token *cur, char c);

// command table
t_cmd					*create_cmd_table(void);
void					fill_cmd_table(void);
void					filling_with_value(t_cmd *cmd_table, t_token **ptr_temp);
int						cmd_has_path(char *cmd);
char					*build_path(char *cmd);
void					copy_cmd_path(char *cmd, char *cmd_path,
							char *split_path);
char					**split_env_path(void);
t_bool					is_builtin(char *cmd);
char					**cmd_to_matrix(t_token **ptr_token);
int						cmd_list_lenght(t_token *token_list);
char					**env_to_matrix(void);
int						env_list_lenght(t_env *env_list);
void					copy_env_matrix(char *env_matrix, t_env *env_list);
int						cmd_count(void);
int						malloc_len(char *key, char *value);
void					save_last_redir_in(t_redir_in **redir);
void					save_last_redir_out(t_redir_out **redir);

// operators
t_bool					is_redir_token(t_token *token);
char					*has_var(char *line);
char					*search_var(char *str);
char					*expand_on_heredoc(char *line);
t_bool					is_redir_token(t_token *token);
void					capture_heredoc(void);
t_token					*handle_redirects(t_cmd *cmd, t_token *current,
							int index);
void					handle_heredoc(t_token *token, t_redir_in **redir_list);
void					handle_redir_in(t_token *token, t_redir_in **redir_list,
							int index);
void					add_redir_in(t_redir_in **redir, t_redir_in *new);
void					add_redir_out(t_redir_out **redir, t_redir_out *new);
t_redir_in				*create_redir_in_list(char *file_name,
									t_type token_type);
t_redir_out				*create_redir_out_list(char *file_name,
									t_type token_type);
t_bool					validate_redir_in_file(char *file, int index);
t_bool					validate_redir_out_file(char *file, int index);
t_bool					file_exists(char *file);
t_bool					file_readable(char *file);
t_bool					file_writable(char *file);
t_bool					is_dir(char *file);

// exec
void					handle_cmd_number(void);
void					exec_builtins(t_cmd *cmd);
void					check_redirects(t_cmd *cmd);
void					exec_one_cmd(t_cmd *cmd_table);
void					exec_mult_cmd(int cmd_number);
void					return_exit_status(void);
void					check_exec(t_cmd *cmd_table);
void					pipe_redirect(int *pipes);
void					dup_pipes_backup(int pipes_backup);
void					update_pipes_backup(int *pipes, int *pipes_backup);
void					wait_child(t_cmd *cmd_table, int cmd_number);
void					child_exec(t_cmd *cmd_table, int pipes_backup);

// builtins
void					cd(char **argv);
void					pwd(char **argv, int fd);
void					echo(char **argv, int fd);
void					env(char **argv, int fd);
void					export(char **argv, int fd);
void					unset(char **argv);
void					exit_shell(char **argv);

// builtins utils
t_bool					is_path(char *path);
void					check_and_insert_vars(char **argv);
char					*valid_sintax_key_and_value_position(char *str);
t_env					*get_node_with_key_equal_to(char *argv);
void					replace_var_value(t_env *var, char *str);
void					add_new_var(char *key, char *value);
void					print_export(t_env *var_list, int fd);
void					print_export_error(char *argv);
int						is_var_name_valid(char *var);
void					print_unset_error(char *argv);
void					delete_env(char *key, t_env **head);

// signals
void					print_quit_or_int(int s);
void					signal_handler(void);
void					execution_signals(int pid);
void					handler_exec(int signal);
void					handler_init(int signum, siginfo_t *info,
							void *context);
void					handle_quit(int signal);
void					signal_heredoc(int pid);
void					ctrl_c_heredoc(int signal);

// utils
int						matrice_len(char **matrice);

// clenup
void					clear_redir_in(t_redir_in **redir);
void					clear_redir_out(t_redir_out **redir);
void					clear_tkn_lst(t_token **token);
void					clear_env_lst(t_env **env);
void					garbage_collect(void *ptr);
void					clear_garbage(void);
void					ft_free_matrice(char **matrice);
void					remove_token(t_token **list, t_token *target);
void					clear_child(void);
void					clear_and_exit_child(int status);
void					clear_child_exec(void);
void					clear_cmd_table(t_cmd *cmd_table);
void					close_fds(void);

// colors
# define COLOR_PINK "\001\x1B[1;35m\002"
# define COLOR_GREEN "\001\x1B[1;32m\002"
# define COLOR_RED "\001\x1B[1;31m\002"
# define COLOR_BLUE "\001\x1B[34m\002"
# define COLOR_YELLOW "\001\x1B[1;33m\002"
# define COLOR_CYAN "\001\x1B[36m\002"
# define COLOR_WHITE "\001\x1B[1;37m\002"
# define COLOR_BLACK "\001\x1B[1;30m\002"
# define COLOR_GRAY "\001\x1B[1;90m\002"
# define COLOR_RESET "\001\x1B\033[0m\002"

#endif
