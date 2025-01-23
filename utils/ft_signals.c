#include "../minishell.h"


static void handle_sigint(int sig) {
    (void)sig;
    printf("\n\033[32mminishell> \033[0m");
    fflush(stdout);
}

static void handle_sigquit(int sig) {
    (void)sig;
    printf("\b\b  \b\b");
    fflush(stdout);
}

void setup_signal_handlers(void) {
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}
