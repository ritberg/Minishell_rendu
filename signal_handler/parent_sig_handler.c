/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_sig_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:03:39 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/31 10:06:02 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
   Function that manages ctrl c, ctrl d and ctrl \

   ctrl + d -> doesn't send signals;
   ctrl + \ -> sends SEGQUIT
   ctrl + c -> exit status is 1
*/

void	handler_sigint(int sig_code)
{
	(void)sig_code;
	printf("\n");
	g_shell->exit_status = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	parent_sig_handler(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}

void	signals_init(sigset_t *set)
{
	sigemptyset(set);
	sigaddset(set, SIGINT);		// ctrl + c == SIGINT, signo = 2
	sigaddset(set, SIGQUIT);	// ctrl + \ == SIGQUIT, signo = 3
	sigaddset(set, SIGTERM);	// ctrl + d == SIGTERM, signo = 15
	sigaddset(set, SIGTSTP);	// ctrl + d == SIGTERM, signo = 15

}

void	signal_handler(sigset_t *set)
{
	signals_init(set);
	parent_sig_handler();
}
