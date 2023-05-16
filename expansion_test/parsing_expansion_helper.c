/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:07:14 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/16 17:53:40 by mdanchev         ###   lausanne.ch       */
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

int	get_new_size(t_token **new)
{
	t_token	*ptr;
	int		size;
	int		i;
	
	size = 0;
	i = 0;
	ptr = *new;
	while (ptr)
	{
		if (ptr->id != DELETE)
		{
			while (ptr->content[i])
			{
				size++;
				i++;
			}
			i = 0;
		}
		ptr = ptr->next;
	}
	return (size);
}


int	join_tokens(t_token **new, t_token *curr)
{
	int	size;
	t_token	*ptr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = get_new_size(new);
	free(curr->content);
	curr->content = NULL;
	if (size == 0)
	{
		free_token(new);
		curr->id = DELETE;
		return (1);
	}
	curr->content = malloc((size + 1) * sizeof(char));
	if (!curr->content)
		return (0);
	ptr = *new;
	while (ptr)
	{
		if (ptr->id == DELETE)
			ptr = ptr->next;
		else
		{
			while (ptr->content[j])
			{
				curr->content[i] = ptr->content[j];
				i++;
				j++;
			}
			ptr = ptr->next;
			j = 0;
		}
	}
	curr->content[i] = '\0';
	free_token(new);
	return (1);
}


int	check_var_exist(t_token *tmp)
{
	if (ft_strncmp(&tmp->content[1], "?", 1) == 0)
	{
		free(tmp->content);
		tmp->content = NULL;
		tmp->content = ft_strdup(ft_itoa(g_shell->exit_status));
		if (!tmp->content)
		{
			malloc_error_print_message("ft_strdup failed");
			return (0);
		}
		return (1);

	}
	else if (ft_strncmp(g_shell->env->var_name, &tmp->content[1], \
				ft_strlen(tmp->content)) == 0)
	{
		free(tmp->content);
		tmp->content = NULL;
		tmp->content = ft_strdup(g_shell->env->var_value);
		if (!tmp->content)
		{
			malloc_error_print_message("ft_strdup failed");
			return (0);
		}
		return (1);
	}
	return (0);
}


int	expand_var(t_token **new)
{
	t_token *tmp;
	t_env	*save;

	tmp = *new;
	save = g_shell->env;
	while (tmp->id != EXPAND)
		tmp = tmp->next;
	while (g_shell->env)
	{
		if (check_var_exist(tmp))
		{
			tmp->id = WORD;
			g_shell->env = save;
			return (ft_strlen(tmp->content));
		}
		g_shell->env = g_shell->env->next;
	}
	tmp->id = DELETE;
	g_shell->env = save;
	return (-1);
}


t_token	*split_tokens(char *s, int start, int len)
{
	t_token *new;

	new = NULL;
	if (start != 0)
	{
		new = new_token(s, 0, start);
		token_linked_list(&new, s, start, len);
		new->next->id = EXPAND;
	}
	else
	{
		new = new_token(s, start, len);
		printf("%p\n", new);
		new->id = EXPAND;
	}
	len = start + len;
	start = len;
	while (s[len])
		len++;
	if (len != start)
		token_linked_list(&new, s,start, len);
	return (new);
}

int	var_len(char *s, int i)
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

int	prepare_expand(t_token *curr, int i)
{
	t_token *new;
	int		len;

	new = NULL;
	len = var_len(curr->content, i);
	new = split_tokens(curr->content, i, len + 1);
	len = expand_var(&new);
	join_tokens(&new, curr);
	if (curr->id == DELETE)
		return (0);
	set_id_expansion(curr);
	if (len == -1)
		return (0);
	return(len + i);
}
