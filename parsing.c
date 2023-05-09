/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:49 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 14:35:10 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_token(t_token **head)
{
	t_token	*tmp;
	
	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
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
	print_token(&token);
	return (token);
}


