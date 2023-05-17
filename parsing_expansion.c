/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/17 14:19:55 by mdanchev         ###   lausanne.ch       */
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

int	loop_double_quotes(char *s, int i)
{
	int		j;
	int		count;

	j = 0;
	count = 0;
	while (s[j] && j < i)
	{
		if (is_simple_quote(s[j]))
			j = loop_simple_quotes(s, i);
		else if (is_double_quote(s[j]))
		{
			count++;
			j++;
		}
		else
			j++;
	}
	if (count != 0 && count % 2 == 0)
		return (0);
	return (1);

}

int	not_within_squotes(t_token *curr, int pos)
{
	int		i;
	int		count;
	int		start;

	i = 0;
	count = 0;
	start = 0;
	printf("pos = %d\n", pos);
	if (!is_dollar(curr->content[pos]))
		return (0);
	while (curr->content[i] && i < pos )
	{
		if (is_double_quote(curr->content[i]))
		{
			i++;
			while (!is_double_quote(curr->content[i]) && i < pos)
				i++;
		}
		else if (is_simple_quote(curr->content[i]))
		{
			start = i;
			i++;
			while (!is_simple_quote(curr->content[i]) && i < pos)
					i++;
			if (pos < i && pos > start)
			{
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

int trim_dollar(t_token *curr, int pos)
{
	int		i;
	int		j;
	char	*s;


	s = NULL;
	i = 0;
	j = 0;
	if (curr->content[pos + 1] == '\'')
	{
		return (1);
	}
	while (curr->content[i])
	{
		if (is_double_quote(curr->content[i]))
		{
			j = loop_double_quotes(curr->content, i);
			if (j == 0)
			{
				return (1);
			}
		}
		i++;
	}
	s = malloc(sizeof(char) * ft_strlen(curr->content) + 1);
	if (!s)
		return (0);
	i = 0;
	while (curr->content[i])
	{
		if (i == pos)
			i++;
		s[j] = curr->content[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(curr->content);
	curr->content = s;
	return (1);
}

int check_dollar(t_token *curr, int pos)
{
	int		i;

	i = pos;
	while (curr->content[i])
	{
		if (is_dollar(curr->content[i]) && not_within_squotes(curr, i))
		{
			if (is_question(curr->content[i + 1]) || \
				(!is_dollar(curr->content[i + 1]) && \
				 !is_quote(curr->content[i + 1]) && \
				 !is_punct(curr->content[i + 1]) && \
				 curr->content[i + 1] != '\0'))
			{
				
				i = prepare_expand(curr, i);
				return (i);
			}
			else if (is_dollar(curr->content[i + 1]))
				i = loop_dollars(curr->content, i);
			else if (is_quote(curr->content[i + 1]))
			{
				i += trim_dollar(curr, i);
				printf("i = %d\n", i);
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



		/*else if (is_punct(curr->content[i + 1]))
		{
			i++;
			while (!is_white_space(curr->content[i]) && tmp->content[i])
				i++;
		}
		}*/
