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

int ft_check_option(char *str)
{
    int i = 0;
    int flag = 0;

    // if (str[0] == '-' && str[1])
    //     flag = 1;
    
        while (str[i])
        {
            if (str[i] == '-')
                flag = 1;
            i++;
        }
    if (flag != 0)
        return (flag);
    return (0);
}

int ft_export(char **matrix)
{
    extern char **environ;
    t_env    *list;
    int i;

    i = -1;
    if (matrix[1] == NULL)
    {
        while (environ[++i])
            printf("%s\n", environ[i]);
    }
    else
    {
        int j = 1;
        list = env_to_lis(environ);
        if (matrix[1][0] == '-' && matrix[1][1])
        {
            printf("%s: %c%c: invalid option\n", matrix[0], matrix[1][0], matrix[1][1]);
            return (2);
        }
        while (matrix[j])
        {
            if (ft_check_option(matrix[j]) == 1)
                printf("%s: not a valid identifier\n", matrix[j]);
            else
                ft_add_env_var(&list, matrix[j]);
            j++;
        }
        free(environ);
        environ = list_to_env(list);
    }
    return (0);
}