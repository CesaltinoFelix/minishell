#include "../minishell.h"


int ft_is_numeric(const char *str) {
    if (!str || !*str) return 0;
    if (*str == '-' || *str == '+') str++;
    while (*str) {
        if (!ft_isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

int	ft_exit(char **args, t_minishell *shell) {
    int exit_code = shell->last_exit_code;
    printf("exit\n");
    
    if (args && args[1]) {
        if (!ft_is_numeric(args[1])) {
            printf("minishell: exit: %s: numeric argument required\n", args[1]);
            exit_code = 255;
        } else if (args[2]) {
            fprintf(stderr, "minishell: exit: too many arguments\n");
            shell->last_exit_code = 1;
            return 1;
        } else {
            exit_code = ft_atoi(args[1]);
        }
    }

    //Nao podemos esquecer de liberar os recursos do minishell aqui
    exit(exit_code);
}
