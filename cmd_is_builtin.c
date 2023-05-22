#include "minishell.h"

// *hhjcmd

int cmd_is_builtin(t_token *token)
{
	if (token && token->id == WORD)
	{
		if (ft_strncmp(token->content, "echo", 5) == 0)
	    	return (1);
		else if (ft_strncmp(token->content, "cd", 3) == 0)
	    	return (1);
    	else if (ft_strncmp(token->content, "pwd", 4) == 0)
	    	return (1);
    	else if (ft_strncmp(token->content, "export", 7) == 0)
	    	return (1);
    	else if (ft_strncmp(token->content, "unset", 6) == 0)
	    	return (1);
    	else if (ft_strncmp(token->content, "env", 4) == 0)
	    	return (1);
    	else if (ft_strncmp(token->content, "exit", 5) == 0)
	    	return (1);
	}
	return (0);
}
