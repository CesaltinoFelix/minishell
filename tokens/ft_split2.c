#include "../minishell.h"

// Função para verificar se um caractere é uma aspa (simples ou dupla)
int ft_check_chr(char c)
{
    return (c == '"' || c == '\'');
}

// Função para contar o número de tokens na string
static size_t count_tokens(const char *s, char c)
{
    size_t count = 0;
    char quote = 0; // Rastreia o tipo de aspa atual

    while (*s)
    {
        if (*s == c && !quote) // Ignora delimitadores fora de aspas
        {
            s++;
            continue;
        }
        count++;
        if (ft_check_chr(*s) && !quote) // Inicia uma aspa
        {
            quote = *s;
            s++;
        }
        while (*s) // Avança até o fim do token
        {
            if (ft_check_chr(*s) && *s == quote) // Fecha a aspa
            {
                quote = 0;
                s++;
                break;
            }
            if (*s == c && !quote) // Encontrou um delimitador fora de aspas
                break;
            s++;
        }
    }
    return count;
}

// Função para obter o início e o comprimento de um token
static void ft_get_start_len(const char *s, char c, const char **start, size_t *len)
{
    char quote = 0; // Rastreia o tipo de aspa atual
    *start = s;

    while (*s)
    {
        if (ft_check_chr(*s) && !quote) // Inicia uma aspa
        {
            quote = *s;
            s++;
        }
        else if (ft_check_chr(*s) && *s == quote) // Fecha a aspa
        {
            quote = 0;
            s++;
        }
        else if (*s == c && !quote) // Encontrou um delimitador fora de aspas
            break;
        else
            s++;
    }
    *len = s - *start;
}

// Função para preencher a matriz de tokens
static void ft_fill_matrix(const char *s, char c, char **result, size_t *i)
{
    const char *start;
    size_t len;

    while (*s)
    {
        if (*s == c) // Ignora delimitadores
        {
            s++;
            continue;
        }
        ft_get_start_len(s, c, &start, &len); // Obtém o próximo token
        result[(*i)++] = ft_strndup(start, len); // Adiciona o token à matriz
        s = start + len; // Avança para o próximo caractere após o token
    }
}

// Função principal para dividir a string em tokens
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
    result[i] = NULL;
    return result;
}