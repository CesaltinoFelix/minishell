/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:14:05 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/15 16:49:25 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_run_execve(t_minishell *shell, int *i, char **path)
{
	char	*tmp;

	while (shell->system_paths[++(*i)])
	{
		if (shell->parsed_input[0][0] == '/'
		|| shell->parsed_input[0][0] == '.')
			execve(shell->parsed_input[0], shell->parsed_input,
				shell->env_variables);
		else
		{
			tmp = ft_strjoin(shell->system_paths[*i], "/");
			if (!*tmp)
				continue ;
			*path = ft_strjoin(tmp, shell->parsed_input[0]);
			free(tmp);
			if (!*path)
				continue ;
			execve(*path, shell->parsed_input, shell->env_variables);
			free(*path);
		}
	}
}

int	execute_external_command(t_minishell *shell)
{
	pid_t	pid;
	char	*path;
	int		i;
	int		signal_status;

	i = -1;
	path = NULL;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		path = getenv("PATH");
		shell->system_paths = ft_split(path, ':');
		if (!shell->system_paths)
			exit(1);
		ft_run_execve(shell, &i, &path);
		ft_write_error(shell->parsed_input[0]);
		ft_free_matrix(shell->system_paths);
		exit(127);
	}
	signal_status = wait_for_signal(pid);
	return (signal_status);
}

int	execute_command(t_minishell *shell)
{
	int		token_count;
	char	**token;
	
	token = shell->parsed_input;
	token_count = ft_matrix_len(shell->parsed_input);
	shell->parsed_input = duplicate_matrix_without_quotes(shell->parsed_input, token_count);
	ft_free_matrix(token);
	if (ft_strcmp(shell->parsed_input[0], "echo") == 0)
		return (handle_echo_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "cd") == 0)
		return (handle_cd_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "pwd") == 0)
		return (handle_pwd_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "export") == 0)
		return (handle_export_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "unset") == 0)
		return (handle_unset_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "env") == 0)
		return (handle_env_command(shell));
	else if (ft_strcmp(shell->parsed_input[0], "exit") == 0)
	{
		handle_exit_command(shell);
		return (shell->exit_status);
	}
	else
		return (execute_external_command(shell));
}

int	aux_process_user_input(t_minishell *shell)
{

	if (get_quote_status(shell->input) == -1)
	{
		shell->exit_status = 2;
		return (1);
	}
	expand_all_env_variables(shell);
	if (!shell->input || *shell->input == '\0')
	{
		shell->exit_status = 0;
		return (1);
	}
	return (0);
}

void	process_user_input(t_minishell *shell)
{
	int			cmd_count;
	t_pipeline	*cmds;

	if (aux_process_user_input(shell))
		return ;
	tokenize_input(shell);
	cmds = split_commands(shell, &cmd_count);
	if (cmd_count > 1)
		execute_pipeline(shell, cmds, cmd_count);
	else
	{
		if (exec_redirection(shell, cmds, cmd_count) == -1)
			return ;
		shell->last_heredoc_file[0] = '\0';
		shell->exit_status = execute_command(shell);
	}
	ft_restore_stdio(shell);
	free_pipeline(cmds, cmd_count);
}
