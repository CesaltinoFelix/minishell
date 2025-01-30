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

typedef struct s_var_exp
{
        int len;
        char *end;
        char *start;
        char *var_name;
        char *var_value;
} t_exp;

typedef struct s_env
{
        char *key;
        char *value;
        char *new_var;
        size_t key_len;
        char *equal_sign;
} t_env;

typedef struct s_minishell
{
        t_env env;
        t_exp exp;
        char *input;
        char **matrix;
        char **env_var;
        char    *old_path;
        char    *current_path;
        int last_exit_code;
} t_minishell;

/* FUNCTIONS */
int is_valid_identifier(const char *str);
char **ft_cpy_env(char *env[]);
void extract_key_value(t_minishell *shell, const char *arg);
void update_or_add_env(t_minishell *shell);
void    ft_sort_string_matrix(char **matrix);
void ft_free_matrix(char **matrix);
char **ft_split_quoted(const char *s, char c) ;
int ft_pwd(void);
int ft_cd(t_minishell *shell);
int ft_env(t_minishell *shell);
int ft_echo(t_minishell *shell);
int ft_exit(t_minishell *shell);
int ft_unset(t_minishell *shell);
int ft_export(t_minishell *shell);

char *ft_strndup(const char *s, size_t len);
int ft_check_quote(char *str);
int ft_strlen_unquote(const char *str);
int ft_strcpy_unquote(char *dest, const char *src, int size);
char **ft_copy_matrix(char **matrix, int size);

#endif
