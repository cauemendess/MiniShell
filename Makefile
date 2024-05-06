HIDE	=	@
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g -I. -I./$(INCDIR)
RFLAGS	=	-lreadline -lhistory

RM		=	rm -rf

NAME	=	minishell
LIBFT	=	libft/libft.a

SRCDIR	=	src/
LEXER	=	lexer/
PARSER	=	parser/
CLEAR	=	clear/
INIT	=	init/
BUILTINS=	builtins/
PROMPT	=	prompt/
SIGNALS	=	signals/
OPERATORS=	operators/
EXEC	=	exec/

SRCS	=	$(SRCDIR)main.c \
			$(SRCDIR)$(LEXER)tokenizer.c \
			$(SRCDIR)$(LEXER)syntax_error.c \
			$(SRCDIR)$(CLEAR)clear.c \
			$(SRCDIR)$(INIT)init_env.c \
			$(SRCDIR)$(LEXER)expansion.c \
			$(SRCDIR)$(LEXER)quotes.c \
			$(SRCDIR)$(BUILTINS)env.c \
			$(SRCDIR)$(BUILTINS)unset.c \
			$(SRCDIR)$(BUILTINS)pwd.c \
			$(SRCDIR)$(BUILTINS)echo.c \
			$(SRCDIR)$(BUILTINS)cd.c \
			$(SRCDIR)$(BUILTINS)export.c \
			$(SRCDIR)$(BUILTINS)exit.c \
			$(SRCDIR)$(PROMPT)prompt_loop.c \
			$(SRCDIR)$(PROMPT)process.c \
			$(SRCDIR)$(SIGNALS)signals.c \
			$(SRCDIR)$(CLEAR)error.c \
			$(SRCDIR)$(OPERATORS)redirect.c \
			$(SRCDIR)$(OPERATORS)heredoc.c \
			$(SRCDIR)$(EXEC)exec_builtins.c \
			$(SRCDIR)$(PARSER)cmd_parse.c \

OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

INCDIR	=	includes/
INC		=	$(INCDIR)minishell.h


all: $(OBJDIR) $(OBJS) $(LIBFT) $(NAME)

$(LIBFT):
	$(HIDE)make -C ./libft --no-print-directory

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(HIDE)mkdir -p $(dir $@)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(HIDE)$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(RFLAGS) -o $@


$(OBJDIR):
	$(HIDE)mkdir -p $@

clean:
	$(HIDE)make -C libft clean
	$(HIDE)$(RM) $(OBJDIR)

fclean: clean
	$(HIDE)make -C libft fclean
	$(HIDE)$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
