#include "./../minishell.h"

extern int g_status;

void heredoc_signal_handler(int sig)
{
    (void)sig;
    g_status = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0); 
    exit(130);
}

void setup_heredoc_signals()
{
    signal(SIGINT, heredoc_signal_handler);
}

void ignore_sigint()
{
    signal(SIGINT, SIG_IGN);
}

void restore_sigint()
{
    signal(SIGINT, sigint_handler);
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
