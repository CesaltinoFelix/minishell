/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcapalan <pcapalan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:52:49 by pcapalan          #+#    #+#             */
/*   Updated: 2025/03/12 19:40:04 by pcapalan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int g_heredoc_interrupted;

int creact_file(char *file)
{
    int fd;
    char *pid_str;
    char *prefix;
    
    prefix = "/tmp/minishell_heredoc_";
    pid_str = ft_itoa(getpid());
    if (!pid_str)
        return (-1);
    ft_strlcpy(file, prefix, 128);
    ft_strlcat(file, pid_str, 128);
    free(pid_str);
    fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);  
    if (fd == -1)
        return (perror("error to open file"),-1);
    return (fd);
}
int configure_signals(struct sigaction *sa_int, struct sigaction *sa_original)
{
    sa_int->sa_handler = sigint_handler;
    sigemptyset(&sa_int->sa_mask);
    sa_int->sa_flags = 0;
    return (sigaction(SIGINT, sa_int, sa_original));
}

int handle_interruption(int fd, char *file)
{
    close(fd);
    unlink(file);
    return (-1);
}

int create_and_validate_heredoc(t_minishell *shell, int i, char *file)
{
    int fd;
    
    fd = creact_file(file);
    if (fd == -1)
    {
        printf("error: could not create heredoc file\n");
        return (-1);
    }
    if (!shell->parsed_input[i + 1])
    {
        printf("syntax error near unexpected token `newline'\n");
        return (-1);   
    }
    return (fd);
}

int read_heredoc_input(int fd, t_minishell *shell, int i, char *file)
{
    char line[128];
    size_t bytes_read;
    
    while (1)
    {
        if (g_heredoc_interrupted)
            return (handle_interruption(fd, file));
        write(1, "> ", 2);
        bytes_read = read(0, line, sizeof(line) - 1);
        if (bytes_read == 0)
        {
            printf("\n");
            printf("warning: here-document at line 12 delimited by end-of-file (wanted `a')\n");
            close(fd);
            unlink(file);
            return -1;
        }
        line[bytes_read - (line[bytes_read - 1] == '\n')] = '\0';
        if (ft_strcmp(line, shell->parsed_input[i + 1]) == 0)
            break;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
    }
    return (close(fd), 0);
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
    char file[128];
    struct sigaction sa_int, sa_original;
    
    g_heredoc_interrupted = 0;
    if (configure_signals(&sa_int, &sa_original) == -1)
        return (-1);
    fd = create_and_validate_heredoc(shell, i, file);
    if (fd == -1)
        return (-1);
    if (read_heredoc_input(fd, shell, i, file) == -1)
        return (-1);
    return (redirect_heredoc_input(shell, file));
}

