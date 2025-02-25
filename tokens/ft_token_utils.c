#include "../minishell.h"

int count_backslashes_before(char *start, char *pos)
{
    int count = 0;
    
    while (pos > start && *(pos - 1) == '\\')
    {
        count++;
        pos--;
    }
    return (count);
}

int get_quote_status(char *str)
{
    int i;
    int status;
    char quote;

    i = 0;
    status = 0;
    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\'') && 
        count_backslashes_before(str, &str[i]) % 2 == 0)
        {
            quote = str[i++];
            if (quote == '"')
                status = 1;
            else
                status = 2;
            while (str[i] && !(str[i] == quote && 
                count_backslashes_before(str, &str[i]) % 2 == 0))
                i++;
            if (!str[i])
                return (-1);
        }
        i++;
    }
    return (status);
}

int unquoted_strlen(const char *str)
{
    int count;
    char quote;

    count = 0; 
    while (*str)
    {
        if (*str == '"' || *str == '\'')
        {
            quote = *str++;
            while (*str && *str != quote)
            {
                count++;
                str++;
            }
            if (*str == quote)
                str++;
        }
        else
        {
            count++;
            str++;
        }
    }
    return (count);
}

int copy_without_quotes(char *dest, const char *src, int max_size)
{
    int i; 
    int j;
    char quote;

    i = 0;
    j = 0;
    while (src[i] && j < max_size)
    {
        if (src[i] == '"' || src[i] == '\'')
        {
            quote = src[i++];
            while (src[i] && src[i] != quote && j < max_size)
                dest[j++] = src[i++];
            if (src[i] == quote)
                i++;
        }
        else
            dest[j++] = src[i++];
    }
    dest[j] = '\0';
    return (i);
}
