/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/16 17:32:07 by mdanchev         ###   lausanne.ch       */
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

int check_dollar(t_token *tmp, int pos)
{
	int		i;

	i = pos;
	while (tmp->content[i])
	{
		if (is_simple_quote(tmp->content[i]))
			i = loop_simple_quotes(tmp->content, i);
		if (is_dollar(tmp->content[i]))
		{
			if (is_question(tmp->content[i + 1]) || \
				(!is_quote(tmp->content[i + 1]) && \
				 !is_dollar(tmp->content[i + 1]) && \
				 !is_punct(tmp->content[i + 1]) && \
				 tmp->content[i + 1] != '\0'))
			{
				
				i = prepare_expand(tmp, i);
				return (i);
			}
			else if (is_dollar(tmp->content[i + 1]))
				i = loop_dollars(tmp->content, i);
			else if (tmp->content[i + 1] == '\0')
				break ;
		}
		else
			i++;
	}
	tmp->id = WORD;
	return (i);
}

void	expansion(t_token **head, int pos)
{
	t_token	*tmp;
	t_token	*next;
	
	tmp = *head;
	next = NULL;
	if (!*head)
		return;
	if (tmp)
	{
		if (tmp->id == DOLLAR)
		{
			pos = check_dollar(tmp, pos);
			if (tmp->id == DELETE)
			{
				delete_token(head);
				if (*head && tmp->next)
				{
					next = tmp->next;
					expansion(&next, pos);
				}
				else
				{
					head = NULL;
					return;
				}
			}
			expansion(&tmp, pos);
		}
		else
		{
			pos = 0;
			if (tmp->next)
			{
				tmp = tmp->next;
				expansion(&tmp, pos);
			}
		}
	}
	return;
}



	/*	else if (is_quote(tmp->content[i + 1]))
		{
	//		trim_dollar(&tmp, &i, i);
			i++;
		}*/
		/*else if (is_punct(tmp->content[i + 1]))
		{
			i++;
			while (!is_white_space(tmp->content[i]) && tmp->content[i])
				i++;
		}
		}*/
