/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:11:25 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/06 18:17:51 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_token(t_token **head)
{
	t_token	*ptr;
	t_token	*tmp;
	
	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = tmp->next;
		free(tmp->content);
		free(tmp->var_value);
		free(tmp);
	}
	*head = NULL;
}

t_token	*new_token(char *tokenp)
{
	t_token	*token;
	int	end;
	int	start;
	
	start = 0;
	end = 0;
	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("malloc: %s\n", strerror(errno));
		return (NULL);
	}
	while (tokenp[end] != '=')
		end++;
	end++;
	token->content = ft_substr(tokenp, 0, end);
	start = end;
	while (tokenp[end] != '\0')
		end++;
	token->var_value = ft_substr(tokenp, start, end - start);
	token->next = NULL;
	return (token);
}

int	link_token(t_token **head, t_token *last)
{
	t_token	*ptr;

	if (!last)
		return (-1);
	ptr = *head;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	ptr->next = last;
	return (0);
}

t_token	**get_tokenp(char **tokenp)
{
	t_token	**head;
	t_token	*token;
	int		i;

	i = 0;
	head = NULL;
	token = new_token(tokenp[i]);
	if (!token)
		return (NULL);
	head = &token;
	i++;
	while (tokenp[i])
	{
		if (link_token(head, new_token(tokenp[i])) < 0)
		{
			free_token(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
