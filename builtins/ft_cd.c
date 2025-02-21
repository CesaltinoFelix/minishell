#include "../minishell.h"

void update_env_vars(t_minishell *shell, const char *key, const char *value)
{
   shell->env.key = ft_strdup(key);
   shell->env.value = ft_strdup(value);
   update_or_add_env(shell);
   free(shell->env.key);
   free(shell->env.value);
}

char *get_env_value(t_minishell *shell, const char *key)
{
   int i;
   size_t key_len;

   i = 0;
   key_len = ft_strlen(key);
   while (shell->env_var[i] != NULL)
   {
      if (ft_strncmp(shell->env_var[i], key, key_len) == 0 && shell->env_var[i][key_len] == '=')
         return (&shell->env_var[i][key_len + 1]);
      i++;
   }
   return (NULL);
}

int change_to_home(t_minishell *shell)
{
   char *home_value;

   home_value = get_env_value(shell, "HOME");
   if (home_value == NULL)
      return (printf("minishell: cd: HOME not set\n"), 1);
   if (chdir(home_value) != 0)
      return (1);
   return (0);
}

int ft_cd(t_minishell *shell)
{
   char buf[128];

   shell->old_path = getcwd(buf, sizeof(buf));
   update_env_vars(shell, "OLDPWD", shell->old_path);
   if (shell->matrix[1] == NULL)
   {
      if (change_to_home(shell) == 1)
         return (2);
   }
   else if (shell->matrix[2] != NULL)
      return (printf("minishell: cd: too many arguments\n"), 2);
   else if (chdir(shell->matrix[1]) == 0)
   {
      shell->current_path = getcwd(buf, sizeof(buf));
      update_env_vars(shell, "PWD", shell->current_path);
   }
   else
   {
      printf("minishell: cd: %s: No such file or directory\n", shell->matrix[1]);
      return (2);
   }
   return (0);
}
