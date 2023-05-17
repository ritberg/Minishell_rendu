/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/17 12:05:18 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	loop_dollars(char *s, int i)
{
	while (is_dollar(s[i]) && s[i])
		i++;
	if (s[i] != '\0')
		i--;
	return (i);
}

int	loop_simple_quotes(char *s, int i)
{
	i++;
	while (!is_simple_quote(s[i]))
		i++;
	return (i);

}

int check_dollar(t_token *curr, int pos)
{
	int		i;

	i = pos;
	while (curr->content[i])
	{
		if (is_simple_quote(curr->content[i]))
			i = loop_simple_quotes(curr->content, i);
		if (is_dollar(curr->content[i]))
		{
			if (is_question(curr->content[i + 1]) || \
				(!is_quote(curr->content[i + 1]) && \
				 !is_dollar(curr->content[i + 1]) && \
				 !is_punct(curr->content[i + 1]) && \
				 curr->content[i + 1] != '\0'))
			{
				
				i = prepare_expand(curr, i);
				return (i);
			}
			else if (is_dollar(curr->content[i + 1]))
				i = loop_dollars(curr->content, i);
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

void	expansion(t_token **head, t_token *curr, int pos)
{
	if (!*head)
		return;
	if (curr)
	{
		if (curr->id == DOLLAR)
		{
			pos = check_dollar(curr, pos);
			if (curr->id == DELETE)
			{
				curr = delete_token(head);
				if (!curr)
				{
					head = NULL;
					return;
				}
			}
			expansion(head, curr, pos);
		}
		else
		{
			pos = 0;
			if (curr->next)
			{
				curr = curr->next;
				expansion(head, curr, pos);
			}
		}
	}
	return;
}



	/*	else if (is_quote(curr->content[i + 1]))
		{
	//		trim_dollar(&curr, &i, i);
			i++;
		}*/
		/*else if (is_punct(curr->content[i + 1]))
		{
			i++;
			while (!is_white_space(curr->content[i]) && tmp->content[i])
				i++;
		}
		}*/
