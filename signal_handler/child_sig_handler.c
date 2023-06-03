/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_sig_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:59:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/03 14:12:15 by mdanchev         ###   lausanne.ch       */
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
	else if (sig_code == SIGTSTP)
	{
		ft_printf("\n");
		g_shell->suspended++;
		ft_printf("[%d]+  Stopped", g_shell->suspended);
	}
	else if (sig_code == SIGSTOP)
	{
		printf("sig stop recieved\n");
	}
	g_shell->exit_status = sig_code + 128;
//	kill(g_shell->pid, sig_code);
}

void	child_signals_init(sigset_t *set)
{
	sigemptyset(set);
	sigaddset(set, SIGINT);		// ctrl + c == SIGINT, signo = 2
	sigaddset(set, SIGQUIT);	// ctrl + \ == SIGQUIT, signo = 3
	sigaddset(set, SIGTERM);	// kill -15 == SIGTERM, signo = 15
	sigaddset(set, SIGTSTP);	// ctrl + z 
	sigaddset(set, SIGSTOP);	// kill -17

}

void	child_signal_handler(int pid)
{
	(void)pid;
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	child_signals_init(&act.sa_mask);
	act.sa_handler = &child_handler;
	sigaction(SIGQUIT, &act, 0); // ctrl + '\'
	sigaction(SIGINT, &act, 0); // ctrl + c
	sigaction(SIGTSTP, &act, 0); // ctrl + z
	sigaction(SIGTERM, &act, 0); // kill -15 PID 
	sigaction(SIGSTOP, &act, &g_shell->sig_term); // kill -17 PID 
}
