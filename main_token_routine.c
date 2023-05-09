/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_token_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:35:09 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 11:35:42 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int g_exit_status = 0;

// Main to test token_linked_list function

int	main(int ac, char **av)
{
	(void)ac;
	t_token	*head;
	t_token	*ptr;
	int		i;
	int		j;
	char	**line;

	i = 0;
	j = 1;
	line = malloc(sizeof(char *) * ac);
	while (av[j])
	{
		line[i] = ft_strdup(av[j]);
		i++;
		j++;
	}
	line[i] = NULL;
	head = NULL;
	head = new_token(line[0], 0, ft_strlen(line[0]));
	if (!head)
	{
		printf("malloc: %s\n", strerror(errno));
		return (1);
	}
	i = 1;
	while (line[i])
	{
		token_linked_list(&head, line[i], 0, ft_strlen(line[i]));
		i++;
	}
	i = 0;
	ptr = head;
	while (ptr)
	{
		printf("%s\n", ptr->content);
		ptr = ptr->next;
		i++;
	}
	free_token(&head);
	return (exit_status);
}
