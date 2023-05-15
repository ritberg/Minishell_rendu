/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/15 17:54:16 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_test_expansion(t_token **head)
{
	t_token *tmp;

	tmp = *head;
	printf("---------test expansion---------\n");
	while (tmp)
	{
		printf("%s|", tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	printf("---------end test expansion---------\n");
}

int	token_list_size(t_token	**head)
{
	t_token	*tmp;
	int		count;

	tmp = *head;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_token	*join_expanded_tokens(t_token **head)
{
	t_token	*tmp;
	int		size;
	char	*ptr;
	char	*new_str;

	tmp = *head;
	new_str = NULL;
	size = token_list_size(head);
	if (size == 1)
	{
		new_str = ft_strdup(tmp->content);
		tmp = new_token(new_str, 0, ft_strlen(new_str));
		free(new_str);
		if ((*head)->id == -1)
			tmp->id = -1;
		free_token(head);
		return (tmp);
	}
	ptr = ft_strjoin(tmp->content, tmp->next->content);
	tmp = tmp->next->next;
	if (tmp)
		new_str = ft_strjoin(ptr, tmp->content);
	else
		new_str = ft_strdup(ptr);
	free(ptr);
	ptr = NULL;
	tmp = new_token(new_str, 0, ft_strlen(new_str));
	if ((*head)->id == -1)
		tmp->id = -1;
	free(new_str);
	free_token(head);
	return (tmp);
}

void	delete_token(t_token **head, int pos)
{
	int		i;
	int		size;
	t_token	*curr;
	t_token	*prev;
	
	i = 0;
	size = token_list_size(head);
	curr = *head;
	prev = *head;
	while (i < pos)
	{
		prev = curr;
		curr = curr->next;
		i++;
	}
	if (i == 0 && size == 1)
	{
		free((*head)->content);
		free(*head);
		head = NULL;
		return ;
	}
	else if (i == 0 && size > 1)
		(*head) = (*head)->next;
	else if (i == size - 1)
		prev->next = NULL;
	else
		prev->next = curr->next;
	free(curr->content);
	free(curr);
	(*head)->id = -1;
}


void	expand_var(t_token **head, int pos)
{
	t_token *tmp;
	t_env	*save;
	int		i;

	i = 0;
	tmp = *head;
	save = g_shell->env;
	while (i < pos)
	{
		tmp = tmp->next;
		i++;
	}
	while (g_shell->env)
	{
		if (ft_strncmp(g_shell->env->var_name, &tmp->content[1], ft_strlen(tmp->content)) == 0)
		{
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = ft_strdup(g_shell->env->var_value);
			g_shell->env = save;
			return;
		}
		g_shell->env = g_shell->env->next;
	}
	delete_token(head, pos);
	g_shell->env = save;
}


t_token	*split_and_join_var(t_token *tmp, int start, int len)
{	
	t_token	*new;
	int		i;
	int		pos;

	new = NULL;
	i = 0;
	pos = 0;
	if (i != start)
	{
		new = new_token(tmp->content, i, start);
		token_linked_list(&new, tmp->content, start, len);
		pos = 1;
	}
	else
		new = new_token(tmp->content, start, len);
	while (i < start + len)
		i++;
	start = i;
	while (tmp->content[i])
		i++;
	if (i != start)
		token_linked_list(&new, tmp->content,start, i);
	expand_var(&new, pos);
	return (join_expanded_tokens(&new));
}


int	prepare_expand(t_token *tmp, int i)
{
	t_token *new;
	int		start;
	int		len;
	
	start = i;
	len = 0;
	i++;
	while (tmp->content[i] && \
			!is_white_space(tmp->content[i]) && \
			!is_quote(tmp->content[i]) && \
			!is_question(tmp->content[i]) && \
			!is_dollar(tmp->content[i]) && \
			!is_punct(tmp->content[i]))
	{
		i++;
		len++;
	}
	new = split_and_join_var(tmp, start, len + 1);
	free(tmp->content);
	tmp->content = NULL;
	tmp->content = ft_strdup(new->content);
	set_id(tmp); //REECRIRE NOUVELLE FC
	if (new->id == -1)
	{
		free_token(&new);
		return (start);

	}
	free_token(&new);
	return(len + start);
}

int check_dollar(t_token *tmp, int pos)
{
	int		i;

	i = pos;
	while (tmp->content[i])
	{
		if (is_simple_quote(tmp->content[i]))
		{
			i++;
			while (!is_simple_quote(tmp->content[i]))
				i++;
		}
		if (is_dollar(tmp->content[i]))
		{
			if (!is_quote(tmp->content[i + 1]) && \
				!is_question(tmp->content[i + 1]) && \
				!is_dollar(tmp->content[i + 1]) && \
				!is_punct(tmp->content[i + 1]) && \
				tmp->content[i + 1] != '\0')
			{
				
				i = prepare_expand(tmp, i);
				return (i);
			}
			else if (is_dollar(tmp->content[i + 1]))
			{
				while (is_dollar(tmp->content[i]))
				{
					i++;
				}
				if (tmp->content[i] != '\0')
				{
					i--;
				}
				else
					break ;
			}
			else if (tmp->content[i + 1] == '\0')
				break ;
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
		}*/
		/*else if (is_punct(tmp->content[i + 1]))
		{
			i++;
			while (!is_white_space(tmp->content[i]) && tmp->content[i])
				i++;
		}
		}*/
		else
			i++;
	//	check_dollar(&tmp);
	}
	tmp->id = WORD;
	return (i);
}

void	expansion(t_token **head, int pos)
{
	t_token	*tmp;
	
	tmp = *head;
	if (tmp)
	{
		if (tmp->id == DOLLAR)
		{
			pos = check_dollar(tmp, pos);
			expansion(&tmp, pos);
		}
		pos = 0;
		if (tmp->next)
			expansion(&tmp->next, pos);
	}
	else
		return;
}



