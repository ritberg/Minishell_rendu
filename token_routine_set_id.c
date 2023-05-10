/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_routine_set_id.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:26:32 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/10 17:07:18 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	set_id(t_token *token)
{
	if (ft_strncmp(token->content, "|", 2) == 0)
		token->id = PIPELINE;
	else if (ft_strncmp(token->content, "<", 2) == 0)
		token->id = L_CHEVRON;
	else if (ft_strncmp(token->content, ">", 2) == 0)
		token->id = R_CHEVRON;
	else if (ft_strncmp(token->content, "<<", 3) == 0)
		token->id = HERE_DOC;
	else if (ft_strncmp(token->content, ">>", 3) == 0)
		token->id = APPEND;
	else if (ft_strchr(token->content, '$'))
		token->id = DOLLAR;
	else
		token->id = WORD;
	return ;
}
