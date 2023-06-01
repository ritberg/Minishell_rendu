/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_sig_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:03:39 by mmakarov          #+#    #+#             */
/*   Updated: 2023/06/01 16:15:41 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
   Function that manages ctrl c, ctrl d and ctrl \

   ctrl + d -> doesn't send signals;
   ctrl + \ -> sends SEGQUIT
   ctrl + c -> exit status is 1
*/
static void handler(int sig_code)
{
	if (sig_code == SIGINT)
	{
		printf("\n");
		g_shell->exit_status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_init(sigset_t *set)
{
	sigemptyset(set);
	sigaddset(set, SIGINT);		// ctrl + c == SIGINT, signo = 2
	sigaddset(set, SIGQUIT);	// ctrl + \ == SIGQUIT, signo = 3
	sigaddset(set, SIGTERM);	// ctrl + d == SIGTERM, signo = 15
	sigaddset(set, SIGTSTP);	// ctrl 

}

void	parent_signal_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	signals_init(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL); // ctrl + \'
	sigaction(SIGTERM, &act, NULL); // kill -15 PID (depuis le terminal)
	sigaction(SIGTSTP, &act, NULL); // ctrl + z
	
	act.sa_handler = handler;
	sigaction(SIGINT, &act, NULL); // ctrl + c
}
