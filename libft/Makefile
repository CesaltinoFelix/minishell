NAME = libft.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

FILES	=	ft_isalpha.c	\
		ft_isdigit.c 		\
		ft_isalnum.c 		\
		ft_isascii.c 		\
		ft_isspace.c		\
		ft_isprint.c 		\
		ft_strlen.c 		\
		ft_memset.c 		\
		ft_bzero.c			\
		ft_memcpy.c 		\
		ft_memmove.c 		\
		ft_strcpy.c			\
		ft_strlcpy.c 		\
		ft_strcat.c		\
		ft_strlcat.c 		\
		ft_toupper.c 		\
		ft_tolower.c 		\
		ft_strchr.c 		\
		ft_strrchr.c 		\
		ft_strcmp.c		\
		ft_strncmp.c 		\
		ft_memchr.c 		\
		ft_memcmp.c 		\
		ft_strnstr.c 		\
		ft_atoi.c 			\
		ft_calloc.c 		\
		ft_strdup.c 		\
		ft_strndup.c		\
		ft_substr.c 		\
		ft_strjoin.c 		\
		ft_strtrim.c 		\
		ft_split.c 			\
		ft_itoa.c 			\
		ft_strmapi.c 		\
		ft_striteri.c 		\
		ft_putchar_fd.c 	\
		ft_putstr_fd.c 		\
		ft_putendl_fd.c 	\
		ft_putnbr_fd.c		\
		ft_puthexa.c		\
		ft_utils.c			\
		ft_printf.c			\
		get_next_line.c 	\
		ft_sort_string_matrix.c \
		get_next_line_utils.c 	

BONUS =		ft_lstnew.c 	\
			ft_lstadd_front.c 	\
			ft_lstsize.c 		\
			ft_lstlast.c 		\
			ft_lstadd_back.c 	\
			ft_lstdelone.c 		\
			ft_lstclear.c 		\
			ft_lstiter.c 		\
			ft_lstmap.c

OBFILES	= $(FILES:.c=.o)
BONUS_FILES	= $(BONUS:.c=.o)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBFILES)
		ar rc $(NAME) $(OBFILES)
		ranlib $(NAME)		

bonus: $(BONUS_FILES)
		ar rc $(NAME) $(BONUS_FILES)
		ranlib $(NAME)

clean:
		rm -f $(OBFILES) $(BONUS_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
