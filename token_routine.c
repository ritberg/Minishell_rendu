/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:11:25 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/06 19:51:27 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// int exit_status = 0;

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
		ft_printf_fd(2, "minishell: malloc: %s\n", strerror(errno));
		exit_status = 1;
		return (NULL);
	}
	token->content = ft_substr(line, start, len);
	if (!token->content)
	{
		exit_status = 1;
		return(free_token(&token), NULL);
	}
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
		return (free_token(head), 0);
	if (!link_token(head, new))
		return (free_token(head), 0);
	return (1);
}

/*
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
*/
