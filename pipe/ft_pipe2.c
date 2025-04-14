/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:28 by cefelix           #+#    #+#             */
/*   Updated: 2025/04/08 09:16:34 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_commands(char **input)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

static int	fill_commands(t_pipeline *cmds, char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		init_cmd(&cmds[j], input, i);
		while (input[i] && ft_strcmp(input[i], "|") != 0)
			i++;
		if (input[i])
			i++;
		cmds[j].is_last = (input[i] == NULL);
		j++;
	}
	return (j);
}

t_pipeline	*split_commands(t_minishell *shell, int *cmd_count)
{
	t_pipeline	*cmds;
	int			num_cmds;

	num_cmds = count_commands(shell->parsed_input);
	cmds = malloc(sizeof(t_pipeline) * (num_cmds + 1));
	if (!cmds)
		return (NULL);
	*cmd_count = fill_commands(cmds, shell->parsed_input);
	return (cmds);
}
