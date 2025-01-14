#include "minishell.h"

static char ft_is_valid_variable(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]) || ft_isalpha(str[i]) || str[i] == '_')
            i++;
        else
            return (str[i]);
    }
    return (str[i]);
}

static int extract_variable_name(t_exp *exp)
{
    exp->len = exp->end - exp->start - 1;
    exp->var_name = malloc(exp->len + 1);
    if (!exp->var_name)
        return 0;
    strncpy(exp->var_name, exp->start + 1, exp->len);
    exp->var_name[exp->len] = '\0';
    return 1;
}

static void replace_variable(char **input, t_exp *exp)
{
    size_t new_len;
    char *new_input;
    new_len = strlen(*input) - (exp->end - exp->start) + strlen(exp->var_value);
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    strncpy(new_input, *input, exp->start - *input);
    strcpy(new_input + (exp->start - *input), exp->var_value);
    strcpy(new_input + (exp->start - *input) + strlen(exp->var_value), exp->end);
    free(*input);
    *input = new_input;
}

static void remove_variable(char **input, t_exp *exp)
{
    size_t new_len;
    char *new_input;

    new_len = strlen(*input) - (exp->end - exp->start);
    new_input = malloc(new_len + 1);
    if (!new_input)
        return;
    strncpy(new_input, *input, exp->start - *input);
    strcpy(new_input + (exp->start - *input), exp->end);
    free(*input);
    *input = new_input;
}

void ft_expand_var(char **input)
{
    t_exp exp;

    while ((exp.start = strchr(*input, '$')) != NULL)
    {
        exp.end = strchr(exp.start + 1, ft_is_valid_variable(exp.start + 1));
        if (exp.end == NULL)
            exp.end = exp.start + strlen(exp.start);
        if (!extract_variable_name(&exp))
            return;
        exp.var_value = getenv(exp.var_name);
        free(exp.var_name);
        if (exp.var_value != NULL)
            replace_variable(input, &exp);
        else
            remove_variable(input, &exp);
    }
}
