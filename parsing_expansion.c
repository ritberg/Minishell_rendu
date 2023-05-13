/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/13 15:19:00 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	expand_var(t_token **head, int *i, int pos)
{
	t_token *tmp;
	t_token *new;
	int		start;
	int		len;
	
	(void)pos;
	tmp = *head;
	start = *i;
	len = 0;
	(*i)++;
	while (tmp->content[*i] && \
			!is_white_space(tmp->content[*i]) && \
			!is_quote(tmp->content[*i]) && \
			!is_question(tmp->content[*i]) && \
			!is_dollar(tmp->content[*i]) && \
			!is_punct(tmp->content[*i]))
	{
		(*i)++;
		len++;
	}
	new = new_token(tmp->content, start, len + 1);
	new->id = WORD;
	printf("expanded = %s\n", new->content);

}

void	check_dollar(t_token **head)
{
	t_token *tmp;
	int		i;
	int		count;
	int		pos;

	tmp = *head;
	i = 0;
	count = 0;
	pos = 0;
	while (tmp->content[i])
	{
		if (tmp->content[i] == '\'')
		{
			while (tmp->content[i] != '\'' && tmp->content[i])
				i++;
		}
		else
		{
			if (tmp->content[i] == '$')
			{
				if (!is_quote(tmp->content[i + 1]) && \
					!is_question(tmp->content[i + 1]) && \
					!is_dollar(tmp->content[i + 1]) && \
					!is_punct(tmp->content[i + 1]) && \
					!ft_isdigit(tmp->content[i + 1]))
				{
					expand_var(&tmp, &i, pos);
					i++;
				}
		/*		else if (is_question (tmp->content[i + 1]))
				{
				//	expand_question(&tmp, &i);
					i++;
				}
				else if (is_quote(tmp->content[i + 1]))
				{
			//		trim_dollar(&tmp, &i, i);
					i++;
				}
				else if (is_dollar(tmp->content[i + 1]))
				{
					while (is_dollar(tmp->content[i]) && count % 2 == 0)
					{
						i++;
						count++;
					}
					i++;
				}
				else if (is_punct(tmp->content[i + 1]))
				{
					i++;
					while (!is_white_space(tmp->content[i]) && tmp->content[i])
						i++;
				}
				else if (ft_isdigit(tmp->content[i + 1]))
				{
				//	expand_digit(&tmp, &i);
					i++;
				}*/
			}
		}
		i++;
		pos++;
	//	check_dollar(&tmp);
	}

}

void	expansion(t_token **head)
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->id == DOLLAR)
			check_dollar(&tmp);
		tmp = tmp->next;
	}
} 
