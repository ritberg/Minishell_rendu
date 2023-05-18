/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:49 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/18 11:14:10 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//FOR TESTING

void	print_token(t_token **head)
{
	int		i;
	t_token	*tmp;

	i = 0;
	if (!*head || !head)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (tmp->id == L_CHEVRON)
			printf("L_CHEVRON: ");
		else if (tmp->id == R_CHEVRON)
			printf("R_CHEVRON: ");
		else if (tmp->id == PIPELINE)
			printf("PIPELINE:  ");
		else if (tmp->id == WORD)
			printf("WORD:      ");
		else if (tmp->id == APPEND)
			printf("APPEND:    ");
		else if (tmp->id == HERE_DOC)
			printf("HERE_DOC:  ");
		else if (tmp->id == DOLLAR)
			printf("DOLLAR:    ");
		while (tmp->content[i])
		{
			printf ("%c", tmp->content[i]);
			i++;
		}
		printf ("%c", tmp->content[i]);
		printf ("\n");
		i = 0;
		tmp = tmp->next;
	}
}

t_token	*parsing(char *line)
{
	t_token	*token;

	if (!syntax_error_check(line))
		return (NULL);
	token = get_tokens(line);
	if (!token)
		return (NULL);
	if (!expansion(&token, token, 0))
		return (NULL);
	if (!quote_removing(&token, token, 0))
		return (NULL);
	print_token(&token); // FOR TESTING
	return (token);
}
