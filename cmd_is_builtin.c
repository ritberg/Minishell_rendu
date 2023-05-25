#include "minishell.h"

// *hhjcmd

int cmd_is_builtin(char *s)
{
	if (s)
	{
		if (ft_strncmp(s, "echo", 5) == 0)
	    	return (1);
		else if (ft_strncmp(s, "cd", 3) == 0)
	    	return (1);
    	else if (ft_strncmp(s, "pwd", 4) == 0)
	    	return (1);
    	else if (ft_strncmp(s, "export", 7) == 0)
	    	return (1);
    	else if (ft_strncmp(s, "unset", 6) == 0)
	    	return (1);
    	else if (ft_strncmp(s, "env", 4) == 0)
	    	return (1);
    	else if (ft_strncmp(s, "exit", 5) == 0)
	    	return (1);
	}
	return (0);
}
