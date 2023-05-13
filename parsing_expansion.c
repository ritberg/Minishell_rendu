/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/13 18:36:17 by mdanchev         ###   lausanne.ch       */
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
	free_token(head);
	tmp = new_token(new_str, 0, ft_strlen(new_str));
	free(new_str);
	return (tmp);
}

// NE MARCHE
void	delete_token(t_token **head)
{
	int		size;
	int		i;
	t_token *ptr;
	t_token *tmp;

	i = 0;
	ptr = *head;
	tmp = *head;
	size = token_list_size(head);
	if (size == 1)
		free_token(head);
	while (ptr)
	{
		if (ptr->content[0] == '$' && i != 0)
		{
			tmp->next = tmp->next->next;
			free(ptr->content);
			free(ptr);
			ptr = tmp;
		}
		else if (ptr->content[0] == '$' && i == 0)
		{
			ptr->next = NULL;
			free(ptr->content);
			free(ptr);
		}
		tmp = ptr;
		ptr = ptr->next;
		i++;
	}
}

void	expand_var(t_token **head)
{
	t_token *tmp;
	t_env	*save;

	tmp = *head;
	save = g_shell->env;
	while (tmp)
	{
		if (tmp->content[0] == '$')
			break;
		tmp = tmp->next;
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
//	delete_token(head);
	g_shell->env = save;
}


t_token	*split_and_join_var(t_token **head, int start, int len)
{	
	t_token	*tmp;
	t_token	*new;
	int		i;

	tmp = *head;
	new = NULL;
	i = 0;
	if (i != start)
	{
		new = new_token(tmp->content, i, start);
		token_linked_list(&new, tmp->content, start, len);
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
	expand_var(&new);
	return (join_expanded_tokens(&new));
}


void	prepare_expand(t_token **head, int i, int pos)
{
	t_token *tmp;
	t_token *new;
	int		start;
	int		len;
	(void)pos;
	
	tmp = *head;
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
	new = split_and_join_var(&tmp, start, len + 1);
	printf("new: %s\n", new->content);
//	insert_token(head, &new, pos);
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
					!is_punct(tmp->content[i + 1]))
				{
					
					prepare_expand(&tmp, i, pos);
					//i++;
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
