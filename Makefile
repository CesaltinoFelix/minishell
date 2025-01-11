NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror -lreadline -lhistory
SRCS =	main.c ft_split2.c ft_utils.c ft_expand_var.c \

OBJS = $(SRCS:.c=.o)
L_DIR = ./libft
LIBFT = $(L_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(CFLAGS) 

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
