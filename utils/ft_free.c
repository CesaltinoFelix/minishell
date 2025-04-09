/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:01:48 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/04 13:38:32 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_pipeline(t_pipeline *cmds, int cmd_count)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = -1;
	while (++i < cmd_count)
	{
		if (cmds[i].cmd_args)
		{
			j = -1;
			while (cmds[i].cmd_args[++j])
				free(cmds[i].cmd_args[j]);
			free(cmds[i].cmd_args);
		}
		if (cmds[i].fd_in != STDIN_FILENO)
			close(cmds[i].fd_in);
		if (cmds[i].fd_out != STDOUT_FILENO)
			close(cmds[i].fd_out);
	}
	free(cmds);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	matrix = NULL;
}

// void	free_t_env_var(t_env_var *env_var)
// {
// 	if (env_var->key)
// 		free(env_var->key);
// 	if (env_var->value)
// 		free(env_var->value);
// 	if (env_var->full_var)
// 		free(env_var->full_var);
// 	if (env_var->equal_sign)
// 		free(env_var->equal_sign);
// }

// void	free_t_var_exp(t_var_exp *var_exp)
// {
// 	if (var_exp->end)
// 		free(var_exp->end);
// 	if (var_exp->start)
// 		free(var_exp->start);
// 	if (var_exp->name)
// 		free(var_exp->name);
// 	if (var_exp->value)
// 		free(var_exp->value);
// }

void	check_to_free(t_minishell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->parsed_input)
	{
		ft_free_matrix(shell->parsed_input);
		shell->parsed_input = NULL;
	}
}
