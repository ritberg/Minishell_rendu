/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_trim_dollar.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:24:54 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/17 17:59:59 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
 * If malloc error -> function return 0
 */
static int	copy_string(t_token *curr, char **s, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	*s = malloc(sizeof(char) * ft_strlen(curr->content) + 1);
	if (!*s)
		return (0);
	i = 0;
	while (curr->content[i])
	{
		if (i == pos)
			i++;
		(*s)[j] = curr->content[i];
		i++;
		j++;
	}
	(*s)[j] = '\0';
	free(curr->content);
	curr->content = *s;
	return (1);
}

/*
 * if copy_string return 0 -> there is a malloc error
 * -> exit the program
 */
int trim_dollar(t_token *curr, int pos)
{
	int		i;
	int		j;
	char	*s;


	s = NULL;
	i = 0;
	j = 0;
	if (curr->content[pos + 1] == '\'')
		return (1);
	while (curr->content[i] && i++)
	{
		if (is_double_quote(curr->content[i]))
		{
			j = loop_double_quotes(curr->content, i);
			if (j == 0)
				return (1);
		}
	}
	if (!copy_string(curr, &s, pos))
		return (0);
	return (1);
}
