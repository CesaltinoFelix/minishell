#include "../minishell.h"

void ft_write_error(char *str)
{
    while (*str)
    write(2, str++, 1);
    ft_putendl_fd(": command not found", 2);
}

void print_invalid_identifier_error(const char *arg)
{
    printf("minishell: export: `%s`: not a valid identifier\n", arg);
}

int validate_unset_option(char **args)
{
    if (args[1] && args[1][0] == '-')
    {
        printf("%s: %s: invalid option\n", args[0], args[1]);
        return (2);
    }
    return (0);
}