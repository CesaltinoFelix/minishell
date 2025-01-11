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
char** ft_copy_matrix(char **matrix, int i);
int	ft_strcpy_quote(char *dest, const char *src, int size);
int ft_strlen_quote(char *str);
void	ft_get_matrix(char *str, char **matrix);
#endif
