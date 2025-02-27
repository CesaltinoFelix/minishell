#include "../minishell.h"

int g_status = 0;

static void sigint_handler(int sig)
{
    (void)sig;
    g_status = 130;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void initialize_signal_handlers()
{
    struct sigaction sa_int;
    
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;

    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction(SIGINT) failed");
        exit(1);
    }
}
