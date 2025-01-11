#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


// typedef struct var_store
// {
//     size_t	i;
//     size_t	len;
// 	char	**result;
//     const char	*start;
// }	t_var_store;

char **ft_split_quoted(const char *s, char c);
char	*ft_strndup(const char *s, size_t	len);

void    ft_expand_variables(char **input);

#endif
