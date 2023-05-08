
#include "minishell.h"

extern int exit_status;

// FOR TESTING PRINTING ENV
/*
void	print_env(t_env	**head)
{
	t_env	*ptr;

	ptr = *head;
	while (ptr)
	{
		ft_printf("print_env function: %s\n", ptr->var_name);
		ft_printf("print_env function: %s\n", ptr->var_value);
		ptr = ptr->next;
	}
}
*/

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	char	*line;
	t_env	*env;
	t_token	*token;
	
	exit_status = 0;
	if (sig_handler() == -1) // a modifier apres le parsing
		return (0);
	while (1)
	{
		env = *get_envp(envp);
		if (!env)
			return (1);
		line = NULL;
		line = readline(BLU_2"minishell$ "RESET);
		if (!line) // s'il y a une erreur de malloc ou CNTR+D
    	{
			rl_clear_history();
			free_env(&env);
			return (0);
    	}
		if (line[0])
			add_history(line);
		printf("EXIT STATUS %d\n", exit_status);
		token = parsing(line);
		exit_status = 0;
		free_token(&token);
		free_env(&env);
	}
	return (0);
}
