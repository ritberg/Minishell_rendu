/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copied.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:04:33 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/12 15:53:49 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
 * 	Here there is a function env_copied to save envp
 *	We will need it for execution later
*/

void	free_tab(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
		free(table[i++]);
	free(table);
}

char	*malloc_strcpy(char *envp)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(envp) + 1));
	if (!str)
		return (free(str), NULL);
	i = 0;
	while (envp[i])
	{
		str[i] = envp[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	col_count(char **table)
{
	size_t	len;

	len = 0;
	while (table[len])
		len++;
	return (len);
}

char	**env_copied(char **envp)
{
	size_t	i;
	size_t	len;
	char	**env_copied;

	len = col_count(envp);
	env_copied = malloc(sizeof(char *) * (len + 1));
	if (!env_copied)
		return (free_tab(env_copied), NULL);
	i = 0;
	while (envp[i])
	{
		env_copied[i] = malloc_strcpy(envp[i]);
		if (!env_copied[i])
			return (free(env_copied[i]), NULL);
		i++;
	}
	env_copied[i] = NULL;
	return (env_copied);
}
/*
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int	i = 0;
	char	**tab = env_copied(envp);
	while (tab[i] != NULL)
		printf("%s\n", tab[i++]);
	return (0);
}
*/
