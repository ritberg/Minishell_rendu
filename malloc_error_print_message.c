/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error_print_message.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:22:35 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/08 11:23:40 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	malloc_error_print_message(char *s)
{
	ft_dprintf(2, "minishell: malloc: %s\n", s);
	exit_status = 1;
}
