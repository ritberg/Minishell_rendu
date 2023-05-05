#include "minishell.h"

void	*free_tab(void **a_free)
{
	if (*a_free)
		free(*a_free);
	*a_free = NULL;
	return (NULL);
}

