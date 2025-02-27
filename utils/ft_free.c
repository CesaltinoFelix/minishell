#include "../minishell.h"

void ft_free_matrix(char **matrix)
{
    int i;
    
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
    matrix = NULL;
}

void free_t_env_var(t_env_var *env_var)
{
    if (env_var->key)
        free(env_var->key);
    if (env_var->value)
        free(env_var->value);
    if (env_var->full_var)
        free(env_var->full_var);
    if (env_var->equal_sign)
        free(env_var->equal_sign);
}

void free_t_var_exp(t_var_exp *var_exp)
{
    if (var_exp->end)
        free(var_exp->end);
    if (var_exp->start)
        free(var_exp->start);
    if (var_exp->name)
        free(var_exp->name);
    if (var_exp->value)
        free(var_exp->value);
}

void check_to_free(t_minishell *shell)
{
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    if (shell->parsed_input)
    {
        ft_free_matrix(shell->parsed_input);
        shell->parsed_input = NULL;
    }
    if (shell->system_paths)
    {
        ft_free_matrix(shell->system_paths);
        shell->system_paths = NULL;
    }
    if (shell->previous_directory)
    {
        free(shell->previous_directory);
        shell->previous_directory = NULL;
    }
    if (shell->current_directory)
    {
        free(shell->current_directory);
        shell->current_directory = NULL;
    }
}

