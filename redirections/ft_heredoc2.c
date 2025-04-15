#include "../minishell.h"

int	create_temp_file(char *file)
{
    int		fd;
    char	*prefix = "/tmp/minishell_heredoc_";

    ft_memcpy(file, prefix, ft_strlen(prefix) + 1);
    fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        perror("error opening file");
    return (fd);
}
int	process_heredoc(t_minishell *shell, int fd, int i, char *file)
{
    signal(SIGINT, heredoc_signal_handler);
    if (read_heredoc_input(fd, shell, i) == -1)
    {
        unlink(file);
        exit(130);
    }
    exit(0);
}

int	handle_heredoc_child(int fd, t_minishell *shell, int i, char *file)
{
    int		pid;
    
    pid = fork();   
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
