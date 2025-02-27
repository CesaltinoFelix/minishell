#include "../minishell.h"

void ft_execute_pipeline(t_minishell *shell)
{
    int i = 0;
    int fd[2];         
    int in_fd = 0;     
    pid_t pid;
    
    while (shell->matrix[i])
    {
        if (ft_strcmp(shell->matrix[i], "|") == 0) 
        {
            pipe(fd); 
            
            pid = fork();
            if (pid == 0) 
            {
                dup2(in_fd, STDIN_FILENO);  
                dup2(fd[1], STDOUT_FILENO); 
                close(fd[0]);  
                ft_execute_bin(shell, i);  
                exit(0);
            }
            else if (pid > 0) 
            {
                waitpid(pid, NULL, 0); 
                close(fd[1]);  
                in_fd = fd[0]; 
            }
            else
            {
                perror("fork");
                return;
            }
        }
        i++;
    }

    
    pid = fork();
    if (pid == 0)
    {
        dup2(in_fd, STDIN_FILENO); 
        ft_execute_bin(shell, i); 
        exit(0);
    }
    else
        waitpid(pid, NULL, 0); 
}
