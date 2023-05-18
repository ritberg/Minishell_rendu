/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_dollar_conditions.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:17:33 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/18 14:21:46 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// does expansion for '$USER' !! A MODIFIER



int	not_within_squotes(t_token *curr, int pos)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!is_dollar(curr->content[pos]))
		return (0);
	while (curr->content[i])
	{
		if (is_double_quote(curr->content[i]))
			i = loop_through(curr->content, i);
		else if (is_simple_quote(curr->content[i]))
		{
			start = i;
			i = loop_through(curr->content, i);
			if (pos > start && pos < i)
				return (0);
		}
		i++;
	}
	return (1);
}

int	is_dollar_to_expand(t_token *curr, int i)
{
	if (is_question(curr->content[i + 1]) || \
		(!is_dollar(curr->content[i + 1]) && \
		!is_quote(curr->content[i + 1]) && \
		!is_punct(curr->content[i + 1]) && \
		curr->content[i + 1] != '\0'))
	{
		return (1);
	}
	return (0);
}
