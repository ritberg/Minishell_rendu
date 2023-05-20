/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:03:39 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/19 12:04:58 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
   Function that manages ctrl c, ctrl d and ctrl \

   ctrl D doesn't send signals;
   ctrl \ sends SEGQUIT

   ! Il faut voir comment retourner le bon exit status
   suivant quelle touche a ete appuye
*/

int	sig_handler(void)
{
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
