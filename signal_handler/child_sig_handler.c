/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:59:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/30 13:29:20 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	child_sigquit(int sig_code)
{
	(void)sig_code;
	ft_printf("QUIT: 3\n");
}

void child_sig_handler(void)
{
	sigset_t	set;

	signals_init(&set);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, child_sigquit);
}
