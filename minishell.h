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
int ft_pwd(void);
int ft_cd(char **matrix);
int ft_exit(char **matrix);
int ft_echo(char **matrix);
int ft_unset(char **matrix);
int ft_env(char **matrix);
int ft_export(char **matrix);

int ft_check_quote(char *str);
void ft_read_inputs(char *input);
void ft_expand_var(char **input);
int ft_strlen_unquote(char *str, int type_quote);
void ft_free_matrix(char **matrix);
int ft_check_cmd(char **matrix);
int ft_strcpy_unquote(char *dest, const char *src, int size, int type_quote);

char *ft_strndup(const char *s, size_t len);
char **ft_split_quoted(const char *s, char c);
char **ft_copy_matrix(char **matrix, int size, int type_quote);
char **ft_get_matrix(char *input, int type_quote);

#endif
