/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_routine_delete.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:46:16 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/16 16:49:52 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	token_list_size(t_token	**head)
{
	t_token	*tmp;
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
void	delete_token(t_token **head)
{
	int		i;
	int		size;
	t_token	*curr;
	t_token	*prev;
	
	i = 0;
	size = token_list_size(head);
	curr = *head;
	prev = *head;
	while (curr->id != DELETE)
	{
		prev = curr;
		curr = curr->next;
		i++;
	}
	if (i == 0 && size == 1)
	{
		free((*head)->content);
		free (*head);
		*head = NULL;
		return ;
	}
	else if (i == 0 && size > 1)
		(*head) = (*head)->next;
	else if (i == size - 1)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->content);
	free(curr);
}
