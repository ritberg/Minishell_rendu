/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:11:25 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/06 18:55:05 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int exit_status = 0;

void	free_token(t_token **head)
{
	t_token	*ptr;
	t_token	*tmp;
	
	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = tmp->next;
		free(tmp->content);
	//	free(tmp->(&id));
		free(tmp);
	}
	*head = NULL;
}

t_token	*new_token(char *line, int start, int len)
{
	t_token	*token;
	
	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("malloc: %s\n", strerror(errno));
		exit_status = 1;
		return (NULL);
	}
	token->content = ft_substr(line, start, len);
	token->id = 0;
	token->next = NULL;
	return (token);
}

int	link_token(t_token **head, t_token *new)
{
	t_token	*ptr;

	if (!new)
		return (0);
	ptr = *head;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	ptr->next = new;
	return (1);
}

int	token_linked_list(t_token **head, char *line, int start, int len)
{
	t_token	*new;
	int		i;

	i = 0;
	if (!head)
		return (1);
	new = new_token(line, start, len);
	if (!new)
		return (0);
	if (!link_token(head, new))
	{
		free_token(head);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	t_token	*head;
	t_token	*ptr;
	int		i;
	char	**line;

	i = 0;
	line = malloc(sizeof(char) * ac);
	printf("av[i + 1] = %s\n", av[i + 1]);
	while (av[i + 1])
	{
		line[i] = ft_strdup(av[i + 1]);
		i++;
	}
	printf("line[0] = %s\n", line[0]);
	line[i] = NULL;
	head = NULL;
	head = new_token(line[0], 0, ft_strlen(line[0]));
	printf("head->content = %s\n", head->content);
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
