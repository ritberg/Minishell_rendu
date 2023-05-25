/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_token_extraction.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:46:32 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 11:30:46 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	exit_status = 0;

/*
   Temporary main
   Goal - create a linked list of extracted words (see get_words(line))
   - save the first element as head
   - if there is no head, return exit_status
   - if there is a head, create a linked list 
   		with a pointer ptr using t_token structure
   - free head
*/

int	main(int ac, char **av)
{
	(void)ac;
	t_token	*head;
	t_token	*ptr;
	char	*line;
	
	line = NULL;
	head = NULL;
	line = ft_strdup(av[1]);
	head = get_words(line);
	if (!head)
	{
		printf(" exit from main\n");
		return (exit_status);
	}
	ptr = head;
	while (ptr)
	{
		printf("from main: %s\n", ptr->content);
		ptr = ptr->next;
	}
	free_token(&head);
	return (exit_status);
}


// Old main to do tests inside this file

/*
int	main(int ac, char **av)
{
	*t_token	*head;
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
*/
