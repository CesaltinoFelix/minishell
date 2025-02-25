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

static size_t get_token_bounds(const char *input, char delimiter)
{
    char quote = 0;
    const char *start = input;

    if (is_redirection(*input))
        return (*(input + 1) == *input) ? 2 : 1;

    skip_token(&input, &quote, delimiter);
    return input - start;
}

static void fill_token_array(const char *input, char delimiter, char **tokens, size_t *index)
{
    size_t length;

    while (*input)
    {
        if (*input == delimiter)
        {
            input++;
            continue;
        }
        length = get_token_bounds(input, delimiter);
        tokens[(*index)++] = ft_strndup(input, length);
        input += length;
    }
}

char **ft_split_quoted(const char *input, char delimiter)
{
    if (!input)
        return NULL;
    size_t index;
    size_t token_count;
    char **tokens;

    index = 0;
    token_count = count_tokens(input, delimiter);
    tokens = malloc(sizeof(char *) * (token_count + 1));
    if (!tokens)
        return NULL;
    fill_token_array(input, delimiter, tokens, &index);
    tokens[index] = NULL;
    return tokens;
}

