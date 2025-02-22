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

static void replace_variable(char **input, t_exp *exp)
{
    size_t  var_len;
    size_t  val_len;
    size_t  new_len;
    size_t  input_len;
    size_t  prefix_len;
    char    *new_input;

    var_len = exp->end - exp->start;
    val_len = ft_strlen(exp->var_value);
    input_len = ft_strlen(*input);
    new_len = input_len - var_len + val_len;
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    prefix_len = exp->start - *input;
    ft_strlcpy(new_input, *input, prefix_len);
    ft_strcpy(new_input + prefix_len, exp->var_value);
    ft_strcpy(new_input + prefix_len + val_len, exp->end);
    free(*input);
    *input = new_input;
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

void ft_expand_var(char **input)
{
    t_exp exp;
    char *current;
    
    current = *input;
    while ((exp.start = ft_strchr(current, '$')) != NULL)
    {
        if (ft_check_escape(*input, exp.start) % 2 == 1)
        {
            current = exp.start + 1;
            continue;
        }
        exp.end = exp.start + 1;
        while (ft_is_valid_variable(*exp.end))
            exp.end++;
        if (exp.end == exp.start + 1) // Se "$" não for seguido de variável
        {
            current = exp.start + 1;
            continue;
        }
        // Extrai o nome da variável
        size_t var_len = exp.end - (exp.start + 1);
        exp.var_name = ft_strndup(exp.start + 1, var_len);
        if (!exp.var_name)
            return;
        exp.var_value = getenv(exp.var_name);
        free(exp.var_name);
        if (exp.var_value)
            replace_variable(input, &exp);
        else
            remove_variable(input, &exp);
        current = *input;
    }
    remove_escape_characters(*input);
}
