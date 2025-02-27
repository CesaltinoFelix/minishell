#include "minishell.h"

int main(int argc, char const *argv[], char *env[])
{
    extern int g_status;
    (void)argc;
    (void)argv;
    t_minishell shell;
    
    initialize_signal_handlers();
    init_shell(&shell, env);
    run_shell(&shell);
    if(g_status == 130)
        shell.exit_status = 130;
    return (shell.exit_status);
}
