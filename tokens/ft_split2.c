#include "../minishell.h"

static size_t count_tokens(const char *s, char c) 
{
    size_t count = 0;

    while (*s) 
    {
        if (*s == c) 
		{
            s++;
            continue;
        }
        count++;
        if (*s == '"') 
        {
            s++;
            while (*s && *s != '"') 
                s++;
            if (*s == '"')
                s++;
        } 
        else 
            while (*s && *s != c && *s != '"')
                s++;
    }
    return count;
}

static void ft_get_start_len_with_quoted(const char *s, char c,  const char **start,  size_t *len)
{
    *start = s++;
    while (*s && *s != '"')
        s++;
    if (*s == '"') 
    {
        s++;
        if(*s != '"')
            while (*s && *s != c && *s != '"')
                s++;
    }
    *len = s - *start;
}

static void ft_get_start_len(const char *s, char c,  const char **start,  size_t *len)
{
    *start = s;
    while (*s && *s != c)
    {
        s++;
        if (*s == '"')
        {
            s++;
            while (*s != '"')
                s++;
        }
    }
    *len = s - *start;
}
static void ft_fill_matrix(const char *s, char c, char **result, size_t *i)
{
    const char *start;
    size_t  len;

    start = NULL;
    while (*s) 
	{
        if (*s == c) 
        {
            s++;
            continue;
        }
        if (*s == '"')
        {
            ft_get_start_len_with_quoted(s, c, &start, &len);
            s += len;
        }
        else 
        {
             ft_get_start_len(s, c, &start, &len);
            s += len;
        }
        result[(*i)++] = ft_strndup(start, len);
    }
} 

char **ft_split_quoted(const char *s, char c) 
{
    char **result;
    size_t i;
    
    i = 0;
    result = NULL;
    if (!s)
        return NULL;
    result = malloc(sizeof(char *) * (count_tokens(s, c) + 1));
    if (!result)
        return NULL;
    ft_fill_matrix(s, c, result, &i);
    result[i] = '\0';
    return result;
}
