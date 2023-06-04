/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_sig_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:03:39 by mmakarov          #+#    #+#             */
/*   Updated: 2023/06/04 11:23:21 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
   Function that manages ctrl c, ctrl d and ctrl \

   ctrl + d -> doesn't send signals;
   SIGQUIT	-> ctrl +\
   SIGINT	-> ctrl + c -> exit status is 1
   SIGTSTP	-> ctrl + z
   SIGKILL -> from command line kill -SIGKILL [pid]
   SIGTERM -> from command line kill -SIGTERM [pid]
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

static void	signals_init(sigset_t *set)
{
	sigemptyset(set);
	sigaddset(set, SIGINT);		
	sigaddset(set, SIGQUIT);	
	sigaddset(set, SIGTERM);	
	sigaddset(set, SIGTSTP);	
	sigaddset(set, SIGKILL);	

}

void	child_signal_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	signals_init(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &act, 0);
	sigaction(SIGINT, &act, 0);
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGKILL, &act, 0);
}

void	parent_signal_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	signals_init(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, 0);
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGTSTP, &act, 0);
	act.sa_handler = handler;
	sigaction(SIGINT, &act, 0);
}
