/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/27 15:21:32 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_for_pipes(t_cmd **head)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = *head;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}	

static int	reset_env_tab(void)
{
	if (g_shell->save_env)
	{
		free_tab2d(g_shell->save_env);
		g_shell->save_env = NULL;
	}
	if (!copy_env_tab())
		return (0);
	return (1);
}

void	execution(t_cmd **head)
{
	int		nb_cmds;

	if (!head || !*head)
		return ;
	nb_cmds = check_for_pipes(head);
	if (!reset_env_tab())
		return ;
	if (nb_cmds == 1)
		one_cmd(*head, head);
//	else
//		pipex(head, nb_cmds);
}
