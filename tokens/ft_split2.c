#include "../minishell.h"

int ft_check_chr(char c)
{
    return (c == '"' || c == '\'');
}

int ft_is_redirect(char c)
{
    return (c == '>' || c == '<');
}

// ✅ Contar tokens corretamente, separando redirecionadores (>, >>, <)
static size_t count_tokens(const char *s, char c)
{
    size_t count = 0;
    char quote = 0;

    while (*s)
    {
        if (*s == c && !quote)
        {
            s++;
            continue;
        }
        count++;

        if (ft_check_chr(*s) && !quote)
        {
            quote = *s;
            s++;
        }
        while (*s)
        {
            if (ft_check_chr(*s) && *s == quote)
            {
                quote = 0;
                s++;
                break;
            }
            if (!quote && ft_is_redirect(*s)) // ✅ Conta ">" e "<" como tokens
            {
                count++;
                if (*(s + 1) == *s) // >> ou <<
                    s++;
                s++;
                break;
            }
            if (*s == c && !quote)
                break;
            s++;
        }
    }
    return count;
}

// ✅ Pegar tokens corretamente, separando operadores (>, >>, <)
static void ft_get_start_len(const char *s, char c, const char **start, size_t *len)
{
    char quote = 0;
    *start = s;

    if (ft_is_redirect(*s)) // ✅ Se for redirecionador, captura separado
    {
        if (*(s + 1) == *s) // >> ou <<
            *len = 2;
        else
            *len = 1;
        return;
    }

    while (*s)
    {
        if (ft_check_chr(*s) && !quote)
        {
            quote = *s;
            s++;
        }
        else if (ft_check_chr(*s) && *s == quote)
        {
            quote = 0;
            s++;
        }
        else if (!quote && ft_is_redirect(*s)) // ✅ Se encontra >, >> ou <, para aqui
            break;
        else if (*s == c && !quote)
            break;
        else
            s++;
    }
    *len = s - *start;
}

// ✅ Preenchendo a matriz corretamente
static void ft_fill_matrix(const char *s, char c, char **result, size_t *i)
{
    const char *start;
    size_t len;

    while (*s)
    {
        if (*s == c)
        {
            s++;
            continue;
        }
        ft_get_start_len(s, c, &start, &len);
        result[(*i)++] = ft_strndup(start, len);
        s = start + len;
    }
}

char **ft_split_quoted(const char *s, char c)
{
    char **result;
    size_t i;

    i = 0;
    if (!s)
        return NULL;
    result = malloc(sizeof(char *) * (count_tokens(s, c) + 1));
    if (!result)
        return NULL;
    ft_fill_matrix(s, c, result, &i);
    result[i] = NULL;
    return result;
}
