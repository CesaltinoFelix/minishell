#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_minishell
{
	int	last_exit_code;
    char **matrix;
} t_minishell;

typedef struct s_var_exp
{
    int len;
    char *start;
    char *end;
    char *var_name;
    char *var_value;
} t_exp;

typedef struct s_env
{
    char **variables;
    int count;
    int *flags;
    char *key;
    char *value;
} t_env;

/* FUNCTIONS */
int ft_compare_str(const char *s1, const char *s2);
void free_env(t_env *env);
void setup_signal_handlers(void);
int ft_pwd(void);
int ft_cd(char **matrix);
int ft_env(char **matrix);
void ft_exit(char **matrix, t_minishell *shell);
int ft_echo(char **matrix);
int ft_unset(char **matrix);
int ft_export(char **matrix);
int ft_check_quote(char *str);
int ft_check_cmd(char **matrix, t_minishell *shell);
int ft_strlen_unquote(char *str, int type_quote);
int ft_strcpy_unquote(char *dest, const char *src, int size, int type_quote);

void ft_read_inputs(char *input, t_minishell *shell);
void ft_expand_var(char **input);
void ft_free_matrix(char **matrix);
void ft_sort_string_matrix(char **matrix);
void	init_shell(t_minishell *shell);

char *ft_strndup(const char *s, size_t len);
char **ft_split_quoted(const char *s, char c);
char **ft_get_matrix(char *input, int type_quote);
char **ft_copy_matrix(char **matrix, int size, int type_quote);

#endif
