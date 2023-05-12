#include "minishell.h"

int is_built_in(t_token *token)
{
	if (token->id == WORD)
	{
		if (ft_strncmp("echo", content, 4))
	    	return (1);
    	if (ft_strncmp("cd", content, 2))
	   		return (1);
    	if (ft_strncmp("pwd", content, 3))
	    	return (1);
    	if (ft_strncmp("export", content, 5))
	    	return (1);
    	if (ft_strncmp("unset", content, 5))
	    	return (1);
    	if (ft_strncmp("env", content, 3))
	    	return (1);
    	if (ft_strncmp("exit", content, 4))
	    	return (1);
	}
	return (0);
}
