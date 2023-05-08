
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

	if (sig_handler() == -1) // a modifier apres le parsing
		return (-1);
	env = *get_envp(envp);
	if (!env)
		return (1);
	while (1)
	{
		line = NULL;
		line = readline(BLU_2"minishell$ "RESET);
		if (line == 0)
    	{
			free(line);
			rl_clear_history();
			return (-1);
    	}
		if (line[0])
			add_history(line);
	   if (!parsing(line))
		   return (exit_status);
	}
	return (1);
}
