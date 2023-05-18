/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/18 15:40:04 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_dollar(t_token *curr, int i)
{
	while (curr->content[i])
	{
		if (is_dollar(curr->content[i]) && not_within_squotes(curr, i))
		{
			if (is_dollar_to_expand(curr, i))
				return (prepare_expand(curr, i));
			else if (is_dollar(curr->content[i + 1]))
				i = loop_dollars(curr->content, i);
			else if (is_quote(curr->content[i + 1]))
			{
				if (!trim_dollar(curr, i))
					return (ERROR_EXIT);
				else
					i = i + 2;
			}
			else if (curr->content[i + 1] == '\0')
				break ;
			else
				i++;
		}
		else
			i++;
	}
	curr->id = WORD;
	return (i);
}

static void	expansion_next_token(t_token **head, t_token *curr, int pos)
{
	pos = 0;
	if (curr->next)
	{
		curr = curr->next;
		expansion(head, curr, pos);
	}
}

int	expansion(t_token **head, t_token *curr, int pos)
{
	if (curr)
	{
		if (curr->id == DOLLAR)
		{
			pos = check_dollar(curr, pos);
			if (pos == ERROR_EXIT)
				return (free_token(head), 0);
			if (curr->id == DELETE)
			{
				curr = delete_token(head);
				if (!curr)
				{
					head = NULL;
					return (1);
				}
				pos = 0;
			}
			expansion(head, curr, pos);
		}
		else
			expansion_next_token(head, curr, pos);
	}
	return (1);
}
