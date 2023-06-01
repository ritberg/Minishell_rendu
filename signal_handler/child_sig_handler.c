/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:59:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/01 17:16:45 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void child_handler(int sig_code)
{
	if (sig_code == SIGINT)
	{
		printf("\n");
	}
	else if (sig_code == SIGQUIT)
	{
		printf("QUIT: 3\n");
	}
}

void	child_signals_init(sigset_t *set)
{
	sigemptyset(set);
	sigaddset(set, SIGINT);		// ctrl + c == SIGINT, signo = 2
	sigaddset(set, SIGQUIT);	// ctrl + \ == SIGQUIT, signo = 3
	sigaddset(set, SIGTERM);	// ctrl + d == SIGTERM, signo = 15
	sigaddset(set, SIGTSTP);	// ctrl 

}

void	child_signal_handler(int pid)
{
	(void)pid;
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	child_signals_init(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGTERM, &act, NULL); // kill -15 PID (depuis le terminal)

		
	act.sa_handler = child_handler;
	sigaction(SIGQUIT, &act, NULL); // ctrl + c
	sigaction(SIGINT, &act, NULL); // ctrl + c
}
