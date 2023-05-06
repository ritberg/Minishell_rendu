/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:49 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/06 18:04:07 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *line)
{
	if (!syntax_error_check(line))
		return (free(line), 1);
	if (!word_extraction(line))
		return (free(line), 1);
}


