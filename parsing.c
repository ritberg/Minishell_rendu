/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:49 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/10 18:02:06 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//FOR TESTING

void	print_token(t_token **head)
{
	t_token	*tmp;
	
	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (tmp->id == L_CHEVRON)
			printf("id = L_CHEVRON\n");
		else if (tmp->id == R_CHEVRON)
			printf("id = R_CHEVRON\n");
		else if (tmp->id == PIPELINE)
			printf("id = PIPELINE\n");
		else if (tmp->id == WORD)
			printf("id = WORD\n");
		else if (tmp->id == APPEND)
			printf("id = APPEND\n");
		else if (tmp->id == HERE_DOC)
			printf("id = HERE_DOC\n");
		else if (tmp->id == DOLLAR)
			printf("id = DOLLAR\n");
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
	print_token(&token); // FOR TESTING
	return (token);
}


