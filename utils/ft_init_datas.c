#include "../minishell.h"

void init_variable_expansion(t_minishell *shell)
{
    shell->var_exp.len = 0;
    shell->var_exp.start = NULL;
    shell->var_exp.end = NULL;
    shell->var_exp.name = NULL;
    shell->var_exp.value = NULL;
}

void init_environment_data(t_minishell *shell)
{
    shell->env_var.key_len = 0;
    shell->env_var.key = NULL;
    shell->env_var.value = NULL;
    shell->env_var.full_var = NULL;
    shell->env_var.equal_sign = NULL;
}

void init_shell(t_minishell *shell, char *env[])
{

    init_variable_expansion(shell);
    init_environment_data(shell);
    shell->env_variables = ft_cpy_env_variables(env);
    shell->input = NULL;
    shell->parsed_input = NULL;
    shell->system_paths = NULL;
    shell->previous_directory = NULL;
    shell->current_directory = NULL;
    shell->last_exit_code = 0;
    shell->exit_status = 0;
    shell->display_exit_status = 0;
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->stdin_backup = dup(STDIN_FILENO);

}
