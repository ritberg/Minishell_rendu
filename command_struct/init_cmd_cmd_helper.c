/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_cmd_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:44:44 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/23 21:45:02 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_cmd_size(t_token **token)
{
	t_token	*ptr;
	int		i;

	i = 0;
	ptr = *token;
	if (!token || !*token)
		return (0);
	while (ptr && ptr->id != PIPELINE)
	{
		if (ptr->id == L_CHEVRON || ptr->id == R_CHEVRON || \
				ptr->id == APPEND || ptr->id == HERE_DOC)
		{
			ptr = ptr->next->next;
		}
		else
		{
			i++;
			ptr = ptr->next;
		}
	}
	return (i);
}
