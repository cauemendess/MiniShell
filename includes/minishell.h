#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_token
{
	char	*command;
	int		token;
	struct	s_token *prev;
	struct	s_token *next;
}	t_token;


typedef struct s_core
{
	char	*input;
	t_token *token;
	t_list	*garbage;
	int		exit_status;
}	t_core;


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
}	t_bool;


// Tokenizer

t_core	*get_core(void);
void	ft_translate_type(int type, int i);
void	ft_print_stack(void);
t_token	*create_tkn_lst(char *command, int type);
void	add_token(t_token **token, t_token *new);
void	save_words(char *input, int start, int end);
void	save_separator(char *input, int pos, int type);
int		check_token(char *str);
void	lexing(char *input);

// Syntax errors

t_bool	simple_error(void);


// Clear
void	clear_tkn_lst(t_token **token);


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
