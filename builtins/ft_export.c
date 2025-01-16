#include "../minishell.h"

t_env *env_to_lis(char *env[])
{
    int i;
    t_env *head = NULL;
    t_env *last = NULL;
    t_env *var;

    i = -1;
    while (env[++i])
    {
        var = malloc(sizeof(t_env));
        var->env_var = ft_strdup(env[i]);
        var->next = NULL;
        if (head == NULL)
            head = var;
        else
            last->next = var;
        last = var;
    }
    return (head);
}

void ft_add_env_var(t_env **head, const char *arg)
{
    t_env *new_env = malloc(sizeof(t_env));
    t_env *tmp = NULL;

    new_env->env_var = ft_strdup(arg);
    new_env->next = NULL;
    if (*head == NULL)
        *head = new_env;
    else
    {
        tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;
    }
    tmp->next = new_env;
}

char **list_to_env(t_env *head)
{
    t_env *tmp;
    int i;
    int count;
    char **new_env;

    i = 0;
    count = 0;
    tmp = head;
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env)
        return (NULL);
    while (i < count)
    {
        new_env[i] = ft_strdup(head->env_var);
        head = head->next;
        i++;
    }
    new_env[count] = NULL;
    return (new_env);
}

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

void ft_export(char **matrix, char *env[])
{
    t_env    *list;
    int i;

    i = -1;
    if (matrix[1] == NULL)
    {
        while (env[++i])
            printf("%s\n", env[i]);
    }
    else
    {
        list = env_to_lis(env);
        // ft_print_litst(list);
        ft_add_env_var(&list, matrix[1]);
        // ft_print_litst(list);
        char **envp = list_to_env(list);
        //ft_free_matrix(env);
        env = envp;
        while (env[++i])
            printf("%s\n", env[i]);
    }
}