#include "../minishell.h"

void update_env_vars(t_minishell *shell, const char *key, const char *value)
{
   shell->env.key = ft_strdup(key);
   shell->env.value = ft_strdup(value);
   update_or_add_env(shell);
   free(shell->env.key);
   free(shell->env.value);
}

int change_to_home(t_minishell *shell)
{
   char *home;
   
   home = getenv("HOME");
   if (home == NULL)
   {
      printf("minishell: cd: HOME not set\n");
      return (1);
   }
   shell->matrix[1] = home;
   return (0);
}

int ft_cd(t_minishell *shell)
{
   char  buf[128];

   shell->old_path = getcwd(buf, sizeof(buf));
   update_env_vars(shell, "OLDPWD", shell->old_path);
   if (shell->matrix[1] == NULL && change_to_home(shell) == 1)
      return (1);
   if (shell->matrix[2] != NULL)
      printf("%s: too many arguments\n", shell->matrix[0]);
   else if (chdir(shell->matrix[1]) == 0)
   {
      shell->current_path = getcwd(buf, sizeof(buf));
      update_env_vars(shell, "PWD", shell->current_path);
   }
   else
      printf("%s: %s: No such file or directory\n", shell->matrix[0], shell->matrix[1]);
   return (0);
}
