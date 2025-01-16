#include "../minishell.h"

void    ft_pwd(void)
{
    char    buf[255];
    
    printf("%s\n", getcwd(buf, sizeof(buf)));
}