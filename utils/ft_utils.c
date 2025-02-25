#include "../minishell.h"

int is_env_var_match(const char *env_var, const char *key, size_t key_len)
{
    return (ft_strncmp(env_var, key, key_len) == 0 &&
            (env_var[key_len] == '=' || env_var[key_len] == '\0'));
}

int validate_unset_option(char **args)
{
    if (args[1] && args[1][0] == '-')
    {
        printf("%s: %s: invalid option\n", args[0], args[1]);
        return (2);
    }
    return (0);
}

int is_valid_env_var_name(const char *name)
{
    int i;

    i = 0;
    if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0] != '_'))
        return (0);
    while (name[i] && name[i] != '=')
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

char *ft_getenv(t_minishell *shell, const char *key)
{
   int i;
   size_t key_len;

   i = 0;
   key_len = ft_strlen(key);
   while (shell->env_var[i] != NULL)
   {
      if (ft_strncmp(shell->env_var[i], key, key_len) == 0 
      && shell->env_var[i][key_len] == '=')
         return (&shell->env_var[i][key_len + 1]);
      i++;
   }
   return (NULL);
}
