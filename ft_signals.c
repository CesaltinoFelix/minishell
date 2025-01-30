#include "minishell.h"

static void handle_sigint(int sig)
{
    (void)sig;
    printf("\n\033[32mminishell> \033[0m");
    fflush(stdout);
}

static void handle_sigquit(int sig)
{
    (void)sig;
}

void setup_signal_handlers(void)
{
    struct sigaction sa_int, sa_quit;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction(SIGINT) failed");
        exit(1);
    }
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
    {
        perror("sigaction(SIGQUIT) failed");
        exit(1);
    }
}
