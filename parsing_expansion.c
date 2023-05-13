/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:13:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/13 16:58:45 by mdanchev         ###   lausanne.ch       */
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
		if (ft_strncmp(&tmp->content[1], g_shell->env->var_name, \
					ft_strlen(&tmp->content[1])) == 0)
		{
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = ft_strdup(g_shell->env->var_value);
			g_shell->env = save;
			return;
		}
		g_shell->env = g_shell->env->next;
	}
	g_shell->env = save;
}


void	split_var(t_token **head, int start, int len)
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
	print_test_expansion(&new);
	expand_var(&new);
	print_test_expansion(&new);
	free_token(&new);
	new = NULL;
	
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
	split_var(&tmp, start, len + 1);
	//insert
	new = new_token(tmp->content, start, len + 1);
	new->id = WORD;
	printf("expanded = %s\n", new->content);
	free_token(&new);

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
