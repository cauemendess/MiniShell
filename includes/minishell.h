/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-m <csilva-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 11:31:47 by csilva-m          #+#    #+#             */
/*   Updated: 2024/04/09 15:39:26 by csilva-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_token
{
	char			*str;
	int				token;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;

}					t_env;

typedef struct s_core
{
	char			*input;
	t_token			*token;
	t_env			*env_list;
	char			**env;
	t_list			*garbage;
	int				exit_status;
	char			invalid;
}					t_core;

enum
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
};

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

// core
t_core				*get_core(void);
void				prompt_loop(void);
void				process(void);
void				ft_translate_type(int type, int i);
void				ft_print_stack(void);
void				error(char *msg, int status, int fd);


//tokenizer
t_token				*create_tkn_lst(char *str, int type);
void				lexing(char *input);
void				add_token(t_token **token, t_token *new);
void				save_words(char *input, int start, int end);
void				save_separator(char *input, int pos, int type);
int					check_token(char *str);

// syntax errors
t_bool				syntax_errors(void);
t_bool				only_spaces(void);
t_bool				check_end_op(void);
t_bool				forbiden_token(void);
t_bool				check_close_quotes(void);
t_bool				check_start_pipe(void);
t_bool				check_op_op(void);
void				split_quotes(char *str, int *i);
void				remove_quote(char *str);

// parser
void				parsing_vars(void);
void				ft_print_env(void);
void				get_env_vars(t_core *core);
void				split_quotes(char *str, int *i);
int					ft_quotes_status(char c, int status);

// clenup
void				clear_tkn_lst(t_token **token);
void				clear_env_lst(t_env **env);
void				garbage_collect(void *ptr);
void				clear_garbage(void);
void				ft_free_matrice(char **matrice);

// builtins

void				env(char **argv);
void				exit_shell(void);

// signals
void				signal_handler(void);

// utils

int					matrice_len(char **matrice);

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
