/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:12:47 by mmakarov          #+#    #+#             */
/*   Updated: 2023/06/10 14:15:40 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	delete_all_heredocs(int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		delete_here_doc(i);
		i++;
	}
	return ;
}
