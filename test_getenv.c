#include <stdio.h>
#include "libft/libft.h"
#include <stdlib.h>
#include <string.h> 
#include <errno.h>

typedef struct s_env
{
	char	*var_name;
	char	*var_value;
	struct s_env	*next;
}	t_env;

void	free_env(t_env **head)
{
	t_env	*ptr;
	t_env	*tmp;
	
	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = tmp->next;
		free(tmp->var_name);
		free(tmp->var_value);
		free(tmp);
	}
	*head = NULL;
}

t_env	*new_env(char *envp)
{
	t_env	*env;
	int	end;
	int	start;
	
	start = 0;
	end = 0;
	env = malloc(sizeof(t_env));
	if (!env)
	{
		printf("malloc: %s\n", strerror(errno));
		return (NULL);
	}
	while (envp[end] != '=')
		end++;
	end++;
	env->var_name = ft_substr(envp, 0, end);
	start = end;
	while (envp[end] != '\0')
		end++;
	env->var_value = ft_substr(envp, start, end - start);
	env->next = NULL;
	return (env);
}

int	link_env(t_env **head, t_env *last)
{
	t_env	*ptr;

	if (!last)
		return (-1);
	ptr = *head;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	ptr->next = last;
	return (0);
}

t_env	**get_envp(char **envp)
{
	t_env	**head;
	t_env	*env;
	int		i;

	i = 0;
	head = NULL;
	env = new_env(envp[i]);
	if (!env)
		return (NULL);
	head = &env;
	i++;
	while (envp[i])
	{
		if (link_env(head, new_env(envp[i])) < 0)
		{
			free_env(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

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
