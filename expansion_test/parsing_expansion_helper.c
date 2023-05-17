/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:07:14 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/17 19:48:09 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int	expand_var(t_token **new)
{
	t_token *tmp;
	t_env	*save;
	int		res;

	tmp = *new;
	save = g_shell->env;
	while (tmp->id != EXPAND)
		tmp = tmp->next;
	while (g_shell->env)
	{
		res = check_var_exist(tmp);
		if (res == ERROR_EXIT)
			return (ERROR_EXIT);
		else if (res == 1)
		{
			tmp->id = EXPANDED;
			g_shell->env = save;
			return (size_var(tmp->content));
		}
		g_shell->env = g_shell->env->next;
	}
	tmp->id = DELETE;
	g_shell->env = save;
	return (-1);
}


int	split_tokens(t_token **new, char *s, int start, int len)
{
	if (start != 0)
	{
		*new = new_token(s, 0, start);
		if (!*new)
			return (ERROR_EXIT);
		if (!token_linked_list(new, s, start, len))
			return (ERROR_EXIT);
		(*new)->next->id = EXPAND;
	}
	else
	{
		*new = new_token(s, start, len);
		if (!*new)
			return (ERROR_EXIT);
		(*new)->id = EXPAND;
	}
	len = start + len;
	start = len;
	while (s[len])
		len++;
	if (len != start)
		if(!token_linked_list(new, s,start, len))
			return (ERROR_EXIT);
	return (1);
}

static int	var_len(char *s, int i)
{
	int		len;
	
	len = 0;
	i++;
	if (is_question(s[i]))
		return (1);
	else
	{
		while (s[i] && \
				!is_white_space(s[i]) && \
				!is_quote(s[i]) && \
				!is_question(s[i]) && \
				!is_dollar(s[i]) && \
				!is_punct(s[i]))
		{
			i++;
			len++;
		}
	}
	return (len);
}

/*
 */
int	prepare_expand(t_token *curr, int i)
{
	t_token *new;
	int		len;

	new = NULL;
	len = var_len(curr->content, i);
	if (split_tokens(&new, curr->content, i, len + 1) == ERROR_EXIT)
		return (free_token(&new), ERROR_EXIT);
	len = expand_var(&new);
	if (len == ERROR_EXIT)
		return (free_token(&new), ERROR_EXIT);
	if (join_tokens(&new, curr) == ERROR_EXIT)
		return (free_token(&new), ERROR_EXIT);
	if (curr->id == DELETE)
		return (0);
	set_id_expansion(curr);
	return(len + i);
}
