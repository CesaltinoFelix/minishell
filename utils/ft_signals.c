#include "../minishell.h"


static void handle_sigint(int sig) {
    (void)sig;
    printf("\ncelson ");
    fflush(stdout);
}

static void handle_sigquit(int sig) {
    (void)sig;
    // printf("\b\b  \b\b");
    printf("cesaltino");
    fflush(stdout);
}

void setup_signal_handlers(void) {
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
}
