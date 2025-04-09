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