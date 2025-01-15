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

char **ft_split_quoted(const char *s, char c) 
{
    char **result;
    size_t i = 0;
    const char *start;
    size_t len;

    if (!s)
        return NULL;
    result = malloc(sizeof(char *) * (count_tokens(s, c) + 1));
    if (!result)
        return NULL;
    while (*s) 
	{
        if (*s == c) 
        {
            s++;
            continue;
        }
        if (*s == '"')
        {
            start = s;
            s++;
            while (*s && *s != '"')
                s++;
            if (*s == '"') 
			{
                s++;
				if(*s != '"')
					while (*s && *s != c && *s != '"')
                		s++;
			}
            len = s - start;
        } 
        else 
        {
            start = s;
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
            len = s - start;
        }
        result[i++] = ft_strndup(start, len);
    }
    result[i] = '\0';
    return result;
}

