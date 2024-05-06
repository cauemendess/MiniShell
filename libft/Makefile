NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADER = libft.h

OBJ_PATH = ./bin/

SOURCES = \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strstr.c \
	ft_replace.c \
	ft_isspace.c \
	ft_strip.c \
	ft_strcmp.c 


BONUS_SOURCES = \
	ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c


OBJECTS = $(addprefix $(OBJ_PATH), $(SOURCES:%.c=%.o))
BONUS_OBJECTS = $(addprefix $(OBJ_PATH), $(BONUS_SOURCES:%.c=%.o))

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJECTS)
	@ar -rcs $(NAME) $?

$(OBJ_PATH)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)
	
$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

bonus:
	@make OBJECTS="$(BONUS_OBJECTS)" --no-print-directory

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PH: all clean re fclean
