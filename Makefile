HIDE	=	@
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -I. -I./$(INCDIR)
RFLAGS	=	-lreadline -lhistory

RM		=	rm -rf

NAME	=	minishell
LIBFT	=	libft/libft.a

SRCDIR	=	src/
SRCS	=	$(SRCDIR)main.c

OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

INCDIR	=	includes/
INC		=	$(INCDIR)minishell.h


all: $(OBJDIR) $(OBJS) $(LIBFT) $(NAME)

$(LIBFT):
	$(HIDE)make -C ./libft

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
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
