/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefelix <cefelix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:02:21 by cefelix           #+#    #+#             */
/*   Updated: 2025/03/20 13:02:22 by cefelix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static int handle_redirection_error(t_minishell *shell, int i)
{
    if (!ft_strcmp(shell->parsed_input[i + 1], ">") ||
        !ft_strcmp(shell->parsed_input[i + 1], "<") ||
        !ft_strcmp(shell->parsed_input[i + 1], ">>") ||
        !ft_strcmp(shell->parsed_input[i + 1], "<<"))
    {
        return (printf("minishell: syntax error near unexpected token `%s'\n", shell->parsed_input[i + 1]), -1);
    }
    return (0);
}

static int handle_output_redir(t_minishell *shell, int i)
{
    int fd;
    int flags;

    if (!shell->parsed_input[i + 1])
        return (printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (handle_redirection_error(shell, i) == -1)
        return (-1);
    if (shell->stdout_backup == -1)
        shell->stdout_backup = dup(STDOUT_FILENO);
    if (!ft_strcmp(shell->parsed_input[i], ">"))
        flags = (O_WRONLY | O_CREAT | O_TRUNC);
    else
        flags = (O_WRONLY | O_CREAT | O_APPEND);
    fd = open(shell->parsed_input[i + 1], flags, 0644);
    if (fd == -1)
        return (perror("minishell: error opening file\n"), -1);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("minishell: error redirecting\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static int handle_input_redir(t_minishell *shell, int i)
{
    int fd;

    if (!shell->parsed_input[i + 1])
        return (printf("minishell: syntax error near unexpected token `newline'\n"), -1);
    if (handle_redirection_error(shell, i) == -1)
        return (-1);
    if (shell->stdin_backup == -1)
        shell->stdin_backup = dup(STDIN_FILENO);
    fd = open(shell->parsed_input[i + 1], O_RDONLY);
    if (fd == -1)
        return (perror("minishell: error opening file\n"), -1);
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: error redirecting\n");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

static void remove_redirection(t_minishell *shell, int i)
{
    int j = i;

    free(shell->parsed_input[j]);
    free(shell->parsed_input[j + 1]);
    while (shell->parsed_input[j + 2])
    {
        shell->parsed_input[j] = shell->parsed_input[j + 2];
        j++;
    }
    shell->parsed_input[j] = NULL;
    shell->parsed_input[j + 1] = NULL;
}

int handle_redirection_aux(t_minishell *shell, int i)
{
    if (!ft_strcmp(shell->parsed_input[i], ">") || !ft_strcmp(shell->parsed_input[i], ">>"))
    {
        if (handle_output_redir(shell, i) == -1)
            return (-1);
    }
    else if (!ft_strcmp(shell->parsed_input[i], "<"))
    {
        if (handle_input_redir(shell, i) == -1)
            return (-1);
    }
    return (0);
}

int ft_handle_redirections(t_minishell *shell)
{
    int i = 0;

    while (shell->parsed_input[i])
    {
        if (!ft_strcmp(shell->parsed_input[i], ">") || !ft_strcmp(shell->parsed_input[i], ">>"))
        {
            if (handle_output_redir(shell, i) == -1)
                return (-1);
        }
        else if (!ft_strcmp(shell->parsed_input[i], "<"))
        {
            if (handle_input_redir(shell, i) == -1)
                return (-1);
        }
        else if (!ft_strcmp(shell->parsed_input[i], "<<"))
        {
            if (ft_handle_heredoc(shell, i) == -1)
                return (-1);
        }
        else
        {
            i++;
            continue;
        }

        remove_redirection(shell, i);
    }
    return (0);
}

void ft_restore_stdio(t_minishell *shell)
{
    if (!shell)
        return;
    if (shell->stdout_backup != -1)
    {
        dup2(shell->stdout_backup, STDOUT_FILENO);
        close(shell->stdout_backup);
        shell->stdout_backup = -1;
    }
    if (shell->stdin_backup != -1)
    {
        dup2(shell->stdin_backup, STDIN_FILENO);
        close(shell->stdin_backup);
        shell->stdin_backup = -1;
    }
}
