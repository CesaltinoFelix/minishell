#include "../minishell.h"

static void update_shell_env(t_minishell *shell, const char *key, const char *value)
{
   shell->env_var.key = ft_strdup(key);
   shell->env_var.value = ft_strdup(value);
   update_or_add_env_var(shell);
   free(shell->env_var.key);
   free(shell->env_var.value);
}

static int change_directory_to_home(t_minishell *shell)
{
   char *home_dir;

   home_dir = ft_getenv(shell, "HOME");
   if (home_dir == NULL)
   {
      printf("minishell: cd: HOME not set\n");
      return (1);
   }
   if (chdir(home_dir) != 0)
      return (1);
   return (0);
}

int handle_cd_command(t_minishell *shell)
{
   char current_dir[128];
   const char *target_dir;

   shell->previous_directory = getcwd(current_dir, sizeof(current_dir));
   update_shell_env(shell, "OLDPWD", shell->previous_directory);
   target_dir = shell->parsed_input[1];
   if (target_dir == NULL)
   {
      if (change_directory_to_home(shell) != 0)
         return (1);
   }
   else if (shell->parsed_input[2] != NULL)
   {
      printf("minishell: cd: too many arguments\n");
      return (1);
   }
   else if (chdir(target_dir) != 0)
   {
      printf("minishell: cd: %s: No such file or directory\n", target_dir);
      return (1);
   }
   shell->current_directory = getcwd(current_dir, sizeof(current_dir));
   update_shell_env(shell, "PWD", shell->current_directory);
   return (0);
}
