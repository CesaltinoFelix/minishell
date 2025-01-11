#include "minishell.h"

char ft_is_valid_variable(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
    {
        if(ft_isdigit(str[i]) || ft_isalpha(str[i])  || str[i] == '_')
            i++;
        else
            return (str[i]);    
    }
    return (str[i]);
}

void ft_expand_variables(char **input) 
{
    char *start, *end, *var_name, *var_value;
    size_t len;
    

    while ((start = strchr(*input, '$'))!= NULL) 
    {
        
        end = strchr(start + 1, ft_is_valid_variable(start + 1));
        if (end == NULL) 
            end = start + strlen(start);
        len = end - start - 1;
        var_name = malloc(len + 1);
        
        strncpy(var_name, start + 1, len);
        var_name[len] = '\0';
        
        var_value = getenv(var_name);
        free(var_name);
        if (var_value != NULL) 
        {
            size_t new_len = strlen(*input) - len + strlen(var_value);
            char *new_input = malloc(new_len + 1);
            strncpy(new_input, *input, start - *input);
            strcpy(new_input + (start - *input), var_value);
            strcpy(new_input + (start - *input) + strlen(var_value), end);
            free(*input);
            *input = new_input;
        }
        else 
        {
            size_t new_len = strlen(*input) - (end - start);
            char *new_input = malloc(new_len + 1);
            strncpy(new_input, *input, start - *input);
            strcpy(new_input + (start - *input), end);
            free(*input);
            *input = new_input;
        }
    }
}