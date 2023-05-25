#include "minishell.h"

/*
   Main to test envp_routine.c
*/
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	**env;
	t_env *ptr;
	env = get_envp(envp);
	if (!env)
		return (2);
	ptr = *env;
	while (ptr != NULL)
	{
		printf("%s", ptr->var_name);
		printf("%s\n", ptr->var_value);
		ptr = ptr->next;
	}
	return(0);
}
