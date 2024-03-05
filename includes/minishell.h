#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_core
{
	char *input;
}	t_core;


typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

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
