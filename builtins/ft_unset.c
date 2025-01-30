#include "../minishell.h"

// Função para comparar duas strings até o '=' ou o final
static int compare_names(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    if ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'))
        return (1);
    return (0);
}

// Função para verificar se uma variável de ambiente deve ser removida
static int should_remove(char *env_var, t_minishell *shell)
{
    int i;
    char *matrix_var;

    i = 0;
    while (shell->matrix[i] != NULL)
    {
        matrix_var = shell->matrix[i];
        if (!is_valid_identifier(matrix_var))
        {
            i++;
            continue;
        }
        if (compare_names(env_var, matrix_var))
        {
            if (ft_strchr(matrix_var, '=') == NULL)
                return (1); // Remove se matrix_var não tem '='
            if (ft_strcmp(env_var, matrix_var) == 0)
                return (1); // Remove se as strings forem iguais
        }
        i++;
    }
    return (0);
}

// Função para contar as variáveis de ambiente que não devem ser removidas
static int count_valid_envs(t_minishell *shell)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (shell->env_var[i] != NULL)
    {
        if (!should_remove(shell->env_var[i], shell))
            count++;
        i++;
    }
    return (count);
}

int ft_aux_unset(char **str)
{
    int i;

    i = 0;
    while (str[i] != NULL)
    {
        if (!is_valid_identifier(str[i]))
        {
            printf("unset: `%s`: not a valid identifier\n", str[i]);
            return (1);
        }
        i++;
    }
    return (0);
}


int ft_unset(t_minishell *shell)
{
    int i;
    int k;
    int valid_count;
    char **new_env;

    i = -1;
    k = 0;
    if (ft_aux_unset(shell->matrix) != 0)
        return (1);
    valid_count = count_valid_envs(shell);
    new_env = malloc(sizeof(char *) * (valid_count + 1));
    if (new_env == NULL)
        return (1);
    while (shell->env_var[++i] != NULL)
    {
        if (!should_remove(shell->env_var[i], shell))
            new_env[k++] = ft_strdup(shell->env_var[i]);
        else
            free(shell->env_var[i]);
    }
    new_env[k] = (NULL);
    ft_free_matrix(shell->env_var);
    shell->env_var = new_env;
    return (0);
}
