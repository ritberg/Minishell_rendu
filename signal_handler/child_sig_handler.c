/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:59:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/31 17:25:01 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	child_sigquit(int sig_code)
{
	(void)sig_code;
	ft_printf("QUIT: 3\n");
}

static void child_sigtstp(int sig_code)
{
	(void)sig_code;

}

static void child_sigint(int sig_code)
{
	(void)sig_code;
	printf("\n");
}

void child_sig_handler(void)
{
	sigset_t	set;

	signals_init(&set);
	signal(SIGINT, child_sigint);// ne marche pas comme id faut
	signal(SIGQUIT, child_sigquit); 
	signal(SIGTSTP, child_sigtstp); // ne marche pas comme il faut
									// +sig_kill ne marche pas
}
