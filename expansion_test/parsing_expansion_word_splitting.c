/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_word_splitting.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:47:25 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/17 10:10:59 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	word_splitting(t_token **new, t_token *curr)
{
	int	i;
	int	size;
	int	nb;
	t_token *tmp;
	
	(void)curr;
	i = 0;
	size = 0;
	nb = 0;
	tmp = *new;
	while (tmp)
	{
		if (tmp->id == EXPANDED)
		{
			while (tmp->content[i])
			{
				if (!is_white_space(tmp->content[i]))
				{
					while (!is_white_space(tmp->content[i]))
					{
						i++;
						size++;
					}
					nb++;
				}
				i++;
			}
			i = 0;
		}
		printf("token = %s\n", tmp->content);
		printf("token id = %d\n", tmp->id);
		tmp = tmp->next;
	}
	printf("nb = %d\n", nb);
	return 0;
}
