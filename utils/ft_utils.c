#include "../minishell.h"

int ft_matrix_len (char **input)
{
    int     i;

    i = 0;
    while (input[i])
        i++;
    return (i);
}

int is_env_var_match(const char *env_var, const char *key, size_t key_len)
{
    return (ft_strncmp(env_var, key, key_len) == 0 &&
            (env_var[key_len] == '=' || env_var[key_len] == '\0'));
}

int is_valid_env_var_name(const char *name)
{
    int i;

    i = 0;
    if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0);
    while (name[i] && name[i] != '=')
    {
        if (!ft_isalpha(name[i]) && !ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

char *trim_whitespace(char *str)
{
    while (*str && ft_isspace(*str))
        str++;
    if (*str == '\0')
        return (ft_strdup(""));
    int end = ft_strlen(str) - 1;
    while (end > 0 && ft_isspace(str[end]))
        end--;
    return (ft_strndup(str, end + 1));
}


void remove_escaped_dollar_and_backslash(char *str)
{
    char *read_ptr; 
    char *write_ptr;
    
    read_ptr = str;
    write_ptr = str;
    while (*read_ptr)
    {
        if (*read_ptr == '\\' && (*(read_ptr + 1) == '$' || *(read_ptr + 1) == '\\'))
            read_ptr++;
        *write_ptr++ = *read_ptr++;
    }
    *write_ptr = '\0';
}


