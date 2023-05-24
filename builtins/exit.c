/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:32:22 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/24 12:12:12 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	free_before_exit(t_cmd **head)
{
	free_shell();
	free_cmd(head);
}

static void	first_argument_is_numeric(t_cmd **head, int size)
{
	int	exit_status;
	
	exit_status = 0;
	if (size == 2)
	{
		printf("exit\n");
		exit_status = ft_atoi((*head)->cmd[1]);
		free_before_exit(head);
		exit (exit_status % 256);
	}
	else if (size > 2)
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		g_shell->exit_status = 1;
	}
}

static int	check_exit_arguments(t_cmd **head)
{
	int	size;

	size = size_tab2d((*head)->cmd);
	if (size == 1)
		return (0);
	if (is_numeric((*head)->cmd[1]))
		first_argument_is_numeric(head, size);
	else
	{
		ft_dprintf(2, "exit\n");
		ft_dprintf(2, "minishell: exit: %s: ", (*head)->cmd[1]);
		ft_dprintf(2, "numeric argument required\n");
		free_before_exit(head);
		exit (255);
	}
	return (1);
}

void	ft_exit(t_cmd **head)
{
	int	res;

	res = check_exit_arguments(head);
	if (!res)
	{
		free_before_exit(head);
		printf("exit\n");
		exit (0);
	}
}
