#include "../minishell.h"


//functions don't used


void    ft_print_litst(t_env *head)
{
    t_env   *tmp;

    tmp = head;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->env_var);
        tmp = tmp->next;
    }
}