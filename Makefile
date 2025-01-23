NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror -lreadline -lhistory
SRCS =	main.c \
	./utils/ft_free.c \
	./utils/ft_signals.c \
	./utils/ft_expand_var.c \
	./tokens/ft_split2.c \
	./tokens/ft_token_utils.c \
	./builtins/ft_echo.c \
	./builtins/ft_cd.c \
	./builtins/ft_pwd.c \
	./builtins/ft_export.c \
	./builtins/ft_unset.c \
	./builtins/ft_env.c \
	./builtins/ft_exit.c 

OBJS = $(SRCS:.c=.o)
L_DIR = ./libft
LIBFT = $(L_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(CFLAGS)
	rm -f $(OBJS)

$(LIBFT):
	$(MAKE) -C $(L_DIR)

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(L_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(L_DIR)

re: fclean all

e: 	all
	./minishell 

.PHONY: all clean fclean re
