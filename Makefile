HIDE =	@
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -I. -I./$(INCDIR)
RFLAGS	=	-lreadline -lhistory

RM		=	rm -rf

NAME	=	minishell

SRCDIR	=	src/
SRCS	=	$(SRCDIR)main.c

OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

INCDIR	=	includes/
INC		=	$(INCDIR)minishell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) $(RFLAGS) -o $@ $^

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(HIDE)mkdir -p $@

clean:
	$(HIDE)$(RM) $(OBJDIR)

fclean: clean
	$(HIDE)$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re