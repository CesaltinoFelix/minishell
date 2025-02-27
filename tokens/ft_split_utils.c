#include "../minishell.h"

int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

int is_redirection(char c)
{
    return (c == '>' || c == '<');
}

void process_token(const char **input, char *quote, char delimiter, size_t *count)
{
    while (**input)
    {
        if (is_quote(**input) && **input == *quote)
        {
            *quote = 0;
            (*input)++;
            break;
        }
        if (*quote == 0 && is_redirection(**input))
        {
            (*count)++;
            if (*(*input + 1) == **input)
                (*input)++;
            (*input)++;
            break;
        }
        if (**input == delimiter && *quote == 0)
            break;
        (*input)++;
    }
}

size_t count_tokens(const char *input, char delimiter)
{
    size_t count = 0;
    char quote = 0;

    while (*input)
    {
        if (*input == delimiter && quote == 0)
        {
            input++;
            continue;
        }
        count++;
        if (is_quote(*input) && quote == 0)
        {
            quote = *input;
            input++;
        }
        process_token(&input, &quote, delimiter, &count);
    }
    return (count);
}

void skip_token(const char **input, char *quote, char delimiter)
{
    while (**input)
    {
        if (is_quote(**input) && *quote == 0)
        {
            *quote = **input;
            (*input)++;
        }
        else if (is_quote(**input) && **input == *quote)
        {
            *quote = 0;
            (*input)++;
        }
        else if (*quote == 0 && (is_redirection(**input) || **input == delimiter))
            break;
        else
            (*input)++;
    }
}