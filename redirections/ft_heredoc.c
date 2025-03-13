/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/13 14:09:03 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int g_heredoc_interrupted;

int create_temp_file(char *file)
{
    int fd;
    char *pid_str;
    char *prefix = "/tmp/minishell_heredoc_";

    pid_str = ft_itoa(getpid());
    if (!pid_str)
        return (-1);
    ft_memcpy(file, prefix, ft_strlen(prefix) + 1);
    ft_strlcat(file, pid_str, 128);
    free(pid_str);
    fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror("error opening file");
    return (fd);
}

int read_heredoc_input(int fd, t_minishell *shell, int i)
{
    char *line;

    while (1)
    {
        if (g_heredoc_interrupted)
            return (-1);
        line = readline("> ");
        if (!line)
        {
            printf("warning: here-document at line 11 delimited by end-of-file (wanted `%s')\n"
            , shell->parsed_input[i + 1]);
            break;
        }
        if (ft_strcmp(line, shell->parsed_input[i + 1]) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    return (0);
}

int process_heredoc(t_minishell *shell, int fd, int i, char *file)
{
    setup_heredoc_signals();
    if (read_heredoc_input(fd, shell, i) == -1)
    {
        unlink(file); // Remove o arquivo temporário em caso de interrupção
        exit(130);
    }
    exit(0);
}

int handle_heredoc_child(int fd, t_minishell *shell, int i, char *file)
{
    int pid = fork();
    
    if (pid == -1)
    {
        perror("fork");
        close(fd);
        unlink(file);
        return (-1);
    }
    if (pid == 0)
        process_heredoc(shell, fd, i, file);
    close(fd);
    return (pid);
}

int redirect_heredoc_input(t_minishell *shell, char *file)
{
    int fd;
   
    if (shell->stdin_backup == -1)
        shell->stdin_backup = dup(STDIN_FILENO);
    if ((fd = open(file, O_RDONLY)) == -1)
    {
        perror("open");
        printf("error: could not open heredoc file\n");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        printf("error: dup2 failed\n");
        return (close(fd), -1);
    }
    close(fd);
    unlink(file);
    return (0);
}

int ft_handle_heredoc(t_minishell *shell, int i)
{
    int fd;
    int pid;
    char file[128];

    g_heredoc_interrupted = 0;
    ignore_sigint(); // Ignorar SIGINT no processo pai
    fd = create_temp_file(file);
    if (!shell->parsed_input[i + 1])
        return(printf("minishell: syntax error near unexpected token `newline'\n"),-1);
    if (fd == -1)
        return (-1);
    pid = handle_heredoc_child(fd, shell, i, file);
    if (pid == -1)
        return (-1);
    if (wait_for_heredoc(shell,pid, file) == -1)
        return (-1);
    restore_sigint(); // Restaurar o comportamento padrão de SIGINT
    return (redirect_heredoc_input(shell, file));
}


