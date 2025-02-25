#include "../minishell.h"

int ft_is_valid_variable(char c)
{
    return (ft_isalnum(c) || c == '_');
}

void remove_escape_characters(char *str)
{
    char *src;
    char *dst;
    
    src = str;
    dst = str;
    while (*src)
    {
        if (*src == '\\' && (*(src + 1) == '$' || *(src + 1) == '\\'))
            src++;
        *dst++ = *src++;
    }
    *dst = '\0';
}

static void replace_variable(t_minishell *shell)
{
    size_t  i;
    size_t  var_len;
    size_t  val_len;
    size_t  new_len;
    size_t  input_len;
    size_t  prefix_len;
    char    *new_input;

    i = -1;
    var_len = shell->exp.end - shell->exp.start;
    val_len = ft_strlen(shell->exp.var_value);
    input_len = ft_strlen(shell->input);
    new_len = input_len - var_len + val_len;
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    prefix_len = shell->exp.start - shell->input;
    while (++i <= prefix_len)
        new_input[i] = ((shell->input))[i];
    ft_strcpy(new_input + prefix_len, shell->exp.var_value);
    ft_strcpy(new_input + prefix_len + val_len, shell->exp.end);
    free(shell->input);
    shell->input = new_input;
}

void remove_variable(char **input, t_exp *exp)
{
    char *new_input;
    size_t new_len;
    size_t prefix_len;
    
    new_len = ft_strlen(*input) - (exp->end - exp->start);
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    prefix_len = exp->start - *input;
    ft_strlcpy(new_input, *input, prefix_len);
    ft_strcpy(new_input + prefix_len, exp->end);
    free(*input);
    *input = new_input;
}

void ft_aux_expand(t_minishell *shell)
{
    size_t var_len;

    if(shell->print_status)
    {
        shell->exp.var_value = ft_itoa(shell->status);
        replace_variable(shell);
        shell->print_status = 0;
    }
    else
    {
        var_len = shell->exp.end - (shell->exp.start + 1);
        shell->exp.var_name = ft_strndup(shell->exp.start + 1, var_len);
        if (!shell->exp.var_name)
            return;
        shell->exp.var_value = ft_getenv(shell, shell->exp.var_name);
        free(shell->exp.var_name);
        if (shell->exp.var_value)
            replace_variable(shell);
        else
            remove_variable(&shell->input, &shell->exp);
    }
}

void ft_expand_var(t_minishell *shell)
{

    char *current;
    
    current = shell->input;
    while ((shell->exp.start = ft_strchr(current, '$')) != NULL)
    {
        if (count_backslashes_before(shell->input, shell->exp.start) % 2 == 1)
        {
            current = shell->exp.start + 1;
            continue;
        }
        shell->exp.end = shell->exp.start + 1;
        if(*(shell->exp.end) == '?')
        {
            shell->print_status = 1;
            shell->exp.end = shell->exp.end + 1;
        }
        else
        {
            while (ft_is_valid_variable(*(shell->exp.end)))
            shell->exp.end++;
            if (shell->exp.end == shell->exp.start + 1)
            {
                current = shell->exp.start + 1;
                continue;
            }
        }
        ft_aux_expand(shell);
        current = shell->input;
    }
    remove_escape_characters(shell->input);
}
