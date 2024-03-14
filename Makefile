HIDE	=	@
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g -I. -I./$(INCDIR)
RFLAGS	=	-lreadline -lhistory

RM		=	rm -rf

NAME	=	minishell
LIBFT	=	libft/libft.a

SRCDIR	=	src/
PARSER	=	parser/
CLEAR	=	clear/
SRCS	=	$(SRCDIR)main.c $(SRCDIR)$(PARSER)tokenizer.c $(SRCDIR)$(CLEAR)clear.c $(SRCDIR)$(PARSER)syntax_error.c

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
	$(HIDE)$(CC) $(CFLAGS) $(RFLAGS) -o $@ $^


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
