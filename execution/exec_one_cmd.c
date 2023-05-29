/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:08:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/29 14:42:10 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	execute_one_bin(t_cmd *cmd, t_cmd **head)
{
	int exit_status;

	exit_status = 0;
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("Fork: "));
	if (cmd->pid == 0)
	{
		execute_bin(cmd);
		exit_status = g_shell->exit_status;
		free_before_exit(head);
		exit(exit_status);
	}
	else
	{
		waitpid(cmd->pid, &cmd->status, 0);
		g_shell->exit_status = WEXITSTATUS(cmd->status);
	}
}

void	one_cmd(t_cmd *cmd, t_cmd **head)
{
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd, head);
	else
		execute_one_bin(cmd, head);
}
