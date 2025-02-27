#include "../minishell.h"

static size_t get_token_bounds(const char *input, char delimiter)
{
    char quote;
    const char *start;
    
    start = input;
    quote = 0;
    if (is_redirection(*input))
    {
        if (*(input + 1) == *input)
            return (2);
        else
            return (1);
    }
    skip_token(&input, &quote, delimiter);
    return (input - start);
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
        return (NULL);
    size_t index;
    size_t token_count;
    char **tokens;

    index = 0;
    token_count = count_tokens(input, delimiter);
    tokens = malloc(sizeof(char *) * (token_count + 1));
    if (!tokens)
        return (NULL);
    fill_token_array(input, delimiter, tokens, &index);
    tokens[index] = NULL;
    return (tokens);
}

