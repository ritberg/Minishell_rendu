
#include "minishell.h"

t_shell	*g_shell;

// FOR TESTING PRINTING ENV
/*
void	print_env(t_env	**head)
{
	t_env	*ptr;

	ptr = *head;
	if (!head || !*head)
		return ;
	while (ptr)
	{
		ft_printf("print_env function: %s\n", ptr->var_name);
		ft_printf("print_env function: %s\n", ptr->var_value);
		ptr = ptr->next;
	}
}
*/

int	init_shell(char **envp)
{
	g_shell = malloc(sizeof(t_shell));
	if (!g_shell)
	{
		ft_dprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (0);
	}
	g_shell->env = get_envp(envp);
	if (!g_shell->env)
	{
		free(g_shell);
		ft_dprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (0);
	}
//	shlvl(g_shell_env);
	g_shell->exit_status = 0;
//	print_env(g_shell->env);
	return (1);
}

void	free_shell(void)
{
	free_env(g_shell->env);
	free(g_shell);
	g_shell = NULL;
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
		return (0);
	while (1)
	{
		line = NULL;
		line = readline(BLU_2"minishell$ "RESET);
		if (!line) // s'il y a une erreur de malloc ou CNTR+D
    	{
			rl_clear_history();
			free_shell();
			return (0);
    	}
		if (line[0])
			add_history(line);
		token = parsing(line);
		printf("from main EXIT STATUS %d\n", g_shell->exit_status);
		g_shell->exit_status = 0;
		free_token(&token);
	}
	return (0);
}
