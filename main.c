
#include "minishell.h"

t_shell	*g_shell;

//extern int g_exit_status;

// FOR TESTING PRINTING ENV

void	print_env()
{
	t_env	*ptr;

	ptr = g_shell->env;
	if (!g_shell || !g_shell->env)
		return ;
	while (g_shell->env)
	{
		ft_printf("print_env function: %s\n", g_shell->env->var_name);
		ft_printf("print_env function: %s\n", g_shell->env->var_value);
		g_shell->env = g_shell->env->next;
	}
	g_shell->env = ptr;
}


void	free_shell(void)
{
	free_env(&g_shell->env);
//	free_tab(g_shell->save_env);
	if (g_shell)
		free(g_shell);
}

int	shell_no_env()
{
	t_env	*env_no;
	env_no = malloc(sizeof(t_env));
	if (!env_no)
	{
		malloc_error_print_message(strerror(errno));
		return (0);
	}
	env_no->var_name = ft_strdup("SHLVL");
	env_no->var_value = ft_strdup("1");
	env_no->next = NULL;
	g_shell->env = env_no;
	return (1);

}

int	init_shell(char **envp)
{
	g_shell = ft_calloc(1, sizeof(t_shell));
	if (!g_shell)
	{
		ft_dprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (0);
	}
	if (!*envp)
	{
		if (!shell_no_env())
			return (0);
	}
	else
	{
		g_shell->env = get_envp(envp);
		if (!g_shell->env)
			return (free_shell(), 0);
	}
	g_shell->exit_status = 0;
	printf("%s\n", g_shell->env->var_name);
	print_env();
	return (1);
}


int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	char	*line;
	t_token	*token;

	if (!init_shell(envp))
		return (1);
	if (sig_handler() == -1) // a modifier apres le parsing
		return (1);
	while (1)
	{
		line = NULL;
		line = readline(BLU_2"minishell$ "RESET);
		if (!line) // s'il y a une erreur de malloc ou CNTR+D
    	{
			rl_clear_history();
			break ;
    	}
		if (line[0])
			add_history(line);

		/* TEST BUILTIN PWD */
		t_cmd	*cmd;
		if (ft_strncmp(line, "pwd", 3) == 0)
		{
			cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				return (0);
			_pwd(cmd);
		}

		token = parsing(line);
//		printf("EXIT STATUS %d\n", g_shell->exit_status);
		g_shell->exit_status = 0;
		free_token(&token);
	}
	free_shell();
	return (0);
}
