/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:39:06 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/20 17:38:26 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	column_size(t_env **head)
{
	t_env	*tmp;
	int		count;

	tmp = *head;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*name_plus_value(char *name, char *value)
{
	char	*joined;
	int		len_name;
	int		len_value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	joined = malloc(sizeof(char) * (len_name + len_value + 2));
	if (!joined)
		return (NULL);
	while (i < len_name)
		joined[i++] = name[j++];
	joined[i] = '=';
	j = 0;
	i++;
	while (j < len_value)
		joined[i++] = value[j++];
	joined[i] = '\0';
	return (joined);
}

char	**copy_env_tab(t_env *env)
{
	char	**res;
	int		column;
	int		i;

	i = 0;
	column = column_size(&env);
	//printf("%d\n", column);  //PRINTF FOR TESTING
	res = malloc(sizeof(char *) * (column + 1));
	if (!res)
		return (NULL);
	while (env)
	{
		res[i] = name_plus_value(env->var_name, env->var_value);
		//printf("%s\n", res[i]);  //PRINTF FOR TESTING
		if (!res[i])
			return (NULL);
		i++;
		env = env->next;
	}
	return (res);
}
