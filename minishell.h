/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:04:26 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/14 15:30:24 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_variable_expansion
{
	int		len;
	char	*end;
	char	*start;
	char	*name;
	char	*value;
}	t_var_exp;

typedef struct s_environment_variable
{
	char	*key;
	char	*value;
	char	*full_var;
	size_t	key_len;
	char	*equal_sign;
}	t_env_var;

typedef struct s_minishell
{
	t_env_var	env_var;
	t_var_exp	var_exp;
	char		*input;
	char		**parsed_input;
	char		**system_paths;
	char		**env_variables;
	char		last_heredoc_file[128];
	char		*previous_directory;
	char		*current_directory;
	int			exit_status;
	int			last_exit_code;
	int			stdout_backup;
	int			stdin_backup;
	int			has_input_redirect;
	int			has_output_redirect;
	int			display_exit_status;
}	t_minishell;

typedef struct s_pipeline
{
	char	**cmd_args;
	int		is_last;
	int		fd_in;
	int		fd_out;
}	t_pipeline;

/* Function Prototypes */
void		print_matrix(char **matrix);
void		ft_write_error(char *str);
void		run_shell(t_minishell *shell);
void		ft_free_matrix(char **matrix);
void		initialize_signal_handlers(void);
void		check_to_free(t_minishell *shell);
void		process_user_input(t_minishell *shell);
void		ft_restore_stdio(t_minishell *shell);
void		update_or_add_env_var(t_minishell *shell);
void		print_sorted_env_vars(t_minishell *shell);
void		init_shell(t_minishell *shell, char *env[]);
void		remove_escaped_dollar_and_backslash(char *str);
void		print_invalid_identifier_error(const char *arg);
void		remove_env_variable_from_input(t_minishell *shell);
void		expand_env_variable(t_minishell *shell);
void		remove_redirection(t_minishell *shell, int i);
void		init_cmd(t_pipeline *cmd, char **input, int i);
void		free_pipeline(t_pipeline *cmds, int cmd_count);
void		execute_pipeline(t_minishell *shell, \
t_pipeline *cmds, int cmd_count);
void		expand_all_env_variables(t_minishell *shell);
void		sigint_handler(int sig);
void		ignore_sigint(void);
void		restore_sigint(void);
void		setup_heredoc_signals(void);
void		heredoc_signal_handler(int sig);
void		handle_exit_command(t_minishell *shell);
void		expand_single_env_variable(t_minishell *shell, char **current);
void		replace_env_variable_in_input(t_minishell *shell);
void		copy_replacement_to_input(t_minishell *shell, char *updated_input,
				size_t chars_before_var, size_t replacement_len);
void		remove_redirection_tokens(char **cmd_args, char *token);
void		handle_child_process(t_minishell *shell, t_pipeline *cmd,
				int prev_pipe_in, int pipes[2]);
void		handle_parent_process(int i, int cmd_count,
				int pipes[2], int *prev_pipe_in);
void		skip_token(const char **input, char *quote, char delimiter);
void		process_token(const char **input, char *quote,
				char delimiter, size_t *count);
void		extract_env_key_value(t_minishell *shell, const char *arg);
void		add_env_var_to_array(t_minishell *shell, char *new_var);

char		*trim_whitespace(char *str);
char		*ft_getenv(t_minishell *shell, const char *key);
char		*create_env_var_string(t_minishell *shell);
char		*allocate_updated_input(size_t updated_len);
char		*get_output_file(char **cmd_args);
char		*get_input_file(char **cmd_args);
int is_append_mode(char **cmd_args);

char		**tokenize_input(t_minishell *shell);
char		**ft_cpy_env_variables(char *env[]);
char		**ft_split_quoted(const char *s, char c);
char		**duplicate_matrix_without_quotes(char **matrix, int size);

int			execute_command(t_minishell *shell);
int			handle_cd_command(t_minishell *shell);
int			handle_env_command(t_minishell *shell);
int			handle_pwd_command(t_minishell *shell);
int			handle_echo_command(t_minishell *shell);
int			handle_unset_command(t_minishell *shell);
int			handle_export_command(t_minishell *shell);
int			wait_for_heredoc(t_minishell *shell, int pid, char *file);
int			ft_aux_expand_single_env(t_minishell *shell, char **current);
int			is_quote(char c);
int			is_redirection(char c);
int			ft_matrix_len(char **input);
int			get_quote_status(char *str);
int			validate_unset_option(char **args);
int			unquoted_strlen(const char *str);
int			execute_external_command(t_minishell *shell);
int			count_backslashes_before(char *str, char *pos);
int			is_valid_env_var_name(const char *name);
int			ft_handle_redirections(t_minishell *shell);
int			copy_without_quotes(char *dest, const char *src, int size);
int			ft_handle_heredoc(t_minishell *shell, int i, char *heredoc_path);
int			is_env_var_match(const char *env_var, \
const char *key, size_t key_len);
int			find_and_update_env_var(t_minishell *shell, char *new_var);
int			create_temp_file(char *file);
int			is_output_redirection(char *str);
int			handle_redirection_error(t_minishell *shell, int i);
int			set_output_flags(char *redir_type);
int			is_builtin(char *cmd);

size_t		count_tokens(const char *input, char delimiter);

t_pipeline	*split_commands(t_minishell *shell, int *cmd_count);

#endif