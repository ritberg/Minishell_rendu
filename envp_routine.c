/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:59:31 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/10 18:17:41 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_env(t_env **head)
{
	t_env	*ptr;
	t_env	*tmp;

//if (!head || !*head)
//	return ;
	ptr = *head;
	while (ptr != NULL)
	{
	printf("hello from free_env\n");
		tmp = ptr;
		ptr = tmp->next;
		free(tmp->var_name);
		free(tmp->var_value);
		free(tmp);
	}
  *head = NULL;
}

/*
   Copy env keys as var_name and values as var_value

   - malloc of t_env structure
   - for var_name, we stop at '=', '=' including
   - for var_value, we stop at '\0'
*/
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
		malloc_error_print_message(strerror(errno));
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

/*
   link all elements of the copied env together
*/
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

/*
   Goal - create a copy of env saving keys and values of env as a linked list

   - save var_name and var_value in the fuction new_env
   - the first line of env becomes head
   - link each element of the linked list in the function link_env
*/
t_env	**get_envp(char **envp)
{
	t_env	**head;
	t_env	*env;
	int		i;

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
	env = new_env(envp[i]);
	if (!env)
		return (NULL);
	head = &env;
	i++;
	while (envp[i])
	{
		if (link_env(head, new_env(envp[i])) < 0)
			return (free_env(head), NULL);
		i++;
	}
	return (head);
}
