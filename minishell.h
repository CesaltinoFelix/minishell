#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_var_exp
{
    int len;
    char *start;
    char *end;
    char *var_name;
    char *var_value;
} t_exp;

/* FUNCTIONS */
int ft_echo_wit_n(char **matrix);
void ft_echo(char **matrix);
void ft_read_inputs(char *input);
void ft_expand_var(char **input);

int ft_check_quote(char *str);
int ft_strlen_unquote(char *str);
int ft_strcpy_unquote(char *dest, const char *src, int size);

char *ft_strndup(const char *s, size_t len);
char *ft_cpy_matrix_to_string(char **matrix);
char **ft_split_quoted(const char *s, char c);
char **ft_copy_matrix(char **matrix, int size);

#endif
