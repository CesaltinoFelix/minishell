#include "./../minishell.h"

extern int g_heredoc_interrupted;

void heredoc_signal_handler(int sig)
{
    (void)sig;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0); 
    exit(130);
}

void setup_heredoc_signals()
{
    struct sigaction sa_int;
    
    sa_int.sa_handler = heredoc_signal_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
}

void ignore_sigint()
{
    struct sigaction sa_ignore;
    
    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sigaction(SIGINT, &sa_ignore, NULL);
}

void restore_sigint()
{
    struct sigaction sa_default;
    
    sa_default.sa_handler = sigint_handler;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sigaction(SIGINT, &sa_default, NULL);
}

int wait_for_heredoc(t_minishell *shell, int pid, char *file)
{
    int status;
    int exit_status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        exit_status = WEXITSTATUS(status);
        if (exit_status == 130)
        {
            shell->exit_status = 130;
            return (unlink(file), -1);
        }
    }
    return (0);
}
