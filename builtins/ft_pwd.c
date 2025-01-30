#include "../minishell.h"

int    ft_pwd()
{
    char    buf[255];
    
    printf("%s\n", getcwd(buf, sizeof(buf)));
    return (0);
}