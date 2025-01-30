#include "../minishell.h"

static void handle_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void setup_signal_handlers(void)
{
    struct  sigaction sa_int;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction(SIGINT) failed");
        exit(1);
    }
}
