#include "minishell.h"


void print_matrix(char **matrix)
{
    int i = -1;
    while (matrix[++i] != NULL)
    {
        printf("[%i] - %s\n", i, matrix[i]);
    }
}