/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:59:31 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/05 17:01:12 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
