#include "../minishell.h"

static void remove_env_variable_from_input(t_minishell *shell)
{

    size_t updated_len;
    size_t  var_name_len;
    size_t chars_before_var;
    char *updated_input;

    var_name_len = shell->var_exp.end - shell->var_exp.start;
    updated_len = ft_strlen(shell->input) - var_name_len;
    updated_input = malloc(sizeof(char) * (updated_len + 1));
    if (!updated_input)
        return;
    chars_before_var = shell->var_exp.start - shell->input;
    ft_memcpy(updated_input, shell->input, chars_before_var);
    ft_strcpy(updated_input + chars_before_var, shell->var_exp.end);
    free(shell->input);
    shell->input = updated_input;
}

static void replace_env_variable_in_input(t_minishell *shell)
{
    size_t  var_name_len = shell->var_exp.end - shell->var_exp.start;
    size_t  replacement_len = ft_strlen(shell->var_exp.value);
    size_t  input_len = ft_strlen(shell->input);
    size_t  updated_len = input_len - var_name_len + replacement_len;
    size_t  chars_before_var = shell->var_exp.start - shell->input;
    char    *updated_input;

    updated_input = malloc(updated_len + 1);
    if (!updated_input)
        return;
    ft_memcpy(updated_input, shell->input, chars_before_var);
    ft_strcpy(updated_input + chars_before_var, shell->var_exp.value);
    ft_strcpy(updated_input + chars_before_var + replacement_len, shell->var_exp.end);
    free(shell->input);
    shell->input = updated_input;
}

void expand_env_variable(t_minishell *shell)
{
    size_t var_name_len;

    if (shell->display_exit_status)
    {
        shell->var_exp.value = ft_itoa(shell->exit_status);
        replace_env_variable_in_input(shell);
        shell->display_exit_status = 0;
        free(shell->var_exp.value);
        return;
    }
    var_name_len = shell->var_exp.end - (shell->var_exp.start + 1);
    shell->var_exp.name = ft_strndup(shell->var_exp.start + 1, var_name_len);
    if (!shell->var_exp.name)
        return;
    shell->var_exp.value = ft_getenv(shell, shell->var_exp.name);
    free(shell->var_exp.name);
    shell->var_exp.name = NULL;
    if (!shell->var_exp.value)
    {
        remove_env_variable_from_input(shell);
        return;
    }
    else
        replace_env_variable_in_input(shell);
}


static void expand_single_env_variable(t_minishell *shell, char **current)
{
    if (count_backslashes_before(shell->input, shell->var_exp.start) % 2 == 1)
    {
        *current = shell->var_exp.start + 1;
        return;
    }
    shell->var_exp.end = shell->var_exp.start + 1;
    if (*(shell->var_exp.end) == '?')
    {
        shell->display_exit_status = 1;
        shell->var_exp.end++;

    }
    else
    {
        while (ft_isalnum(*(shell->var_exp.end)) || *(shell->var_exp.end) == '_')
            shell->var_exp.end++;
        if (shell->var_exp.end == shell->var_exp.start + 1)
        {
            *current = shell->var_exp.start + 1;
            return;
        }
    }
    expand_env_variable(shell);
    *current = shell->input;
}

void expand_all_env_variables(t_minishell *shell)
{
    char *current;
    
    current = shell->input;
    while ((shell->var_exp.start = ft_strchr(current, '$')) != NULL)
        expand_single_env_variable(shell, &current);
    remove_escaped_dollar_and_backslash(shell->input);
}

