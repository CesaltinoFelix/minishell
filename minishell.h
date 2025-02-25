#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
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
        char    **sv_path;
        char **env_var;
        char    *old_path;
        char    *current_path;
        int status;
        int last_exit_code;
        int stdout_backup;
        int stdin_backup;
        int	has_redirect_in;
        int	has_redirect_out;
        int     print_status;
} t_minishell;

void    setup_signal_handlers(void);
void    ft_free_matrix(char **matrix);
void    check_to_free(t_minishell *shell);
void    ft_expand_var(t_minishell *shell);
void    ft_sort_string_matrix(char **matrix);
void    ft_restore_stdio(t_minishell *shell);
void    update_or_add_env_var(t_minishell *shell);
void    print_sorted_env_vars(t_minishell *shell);
void    print_invalid_identifier_error(const char *arg);

char    **ft_cpy_env(char *env[]);
char    *ft_strndup(const char *s, size_t len);
char    **ft_split_quoted(const char *s, char c) ;
char    **duplicate_matrix_without_quotes(char **matrix, int size);
char    *ft_getenv(t_minishell *shell, const char *key);

int     handle_cd_command(t_minishell *shell);
int     handle_env_command(t_minishell *shell);
int     handle_pwd_command(t_minishell *shell);
int     handle_echo_command(t_minishell *shell);
void    handle_exit_command(t_minishell *shell);
int     handle_unset_command(t_minishell *shell);
int     handle_export_command(t_minishell *shell);

int     is_quote(char c);
int     get_quote_status(char *str);
int     validate_unset_option(char **args);
int     unquoted_strlen(const char *str);
int     count_backslashes_before(char *str, char *pos);
int     is_valid_env_var_name(const char *name);
int     ft_handle_redirections(t_minishell *shell);
int     copy_without_quotes(char *dest, const char *src, int size);
int     is_env_var_match(const char *env_var, const char *key, size_t key_len);

#endif
