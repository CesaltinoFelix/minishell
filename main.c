#include "minishell.h"


void	first_token(char *str)
{
	char	**arg;
	int	i;

	i = 0;
	arg = ft_split_quoted(str, ' ');

	while (arg[i])
	{
		printf("token[%d] = %s\n", i, arg[i]);
		i++;
	}
}

int	main(int argc, char **argv, char *env[])
{
	char *input;
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input  = readline("> ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		if (input[0] != '\0')
			add_history(input);
		ft_expand_variables(&input);
		printf("Before tokens: %s\n", input);
		first_token(input);
		//printf("After tokens: %s\n", input);
	}
	return (0);
}
