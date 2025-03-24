NAME = minishell
CC = cc
CFLAGS =  -Wall -Wextra -Werror -lreadline -lhistory
SRCS =	main.c \
	ft_execute.c \
	./utils/ft_free.c \
	./utils/ft_utils.c \
	./utils/ft_signals.c \
	./utils/ft_init_datas.c \
	./utils/ft_file_error.c \
	./utils/ft_expand_var.c \
	./utils/ft_export_utils.c \
	./tokens/ft_split2.c \
	./tokens/ft_split_utils.c \
	./tokens/ft_token_utils.c \
	./builtins/ft_echo.c \
	./builtins/ft_cd.c \
	./builtins/ft_pwd.c \
	./builtins/ft_export1.c \
	./builtins/ft_export2.c \
	./builtins/ft_unset.c \
	./builtins/ft_env.c \
	./builtins/ft_exit.c \
	./utils/ft_manipulation_str.c \
	./redirections/ft_heredoc1.c \
	./redirections/ft_heredoc2.c \
	./redirections/ft_redirections.c \
	./redirections/ft_heredoc_utils.c \
	./redirections/ft_pipe1.c \
	./redirections/ft_pipe2.c \
	./debug.c 

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
	clear
	./minishell 

push:
	git add .
	git commit -m "Updating code"
	git push

.PHONY: all clean fclean re push
