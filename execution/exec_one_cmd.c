/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:08:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/31 12:01:25 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	execute_one_bin(t_cmd *cmd)
{
	int	sig_code;

	sig_code = 0;
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("Fork: "));
	child_sig_handler();
	if (cmd->pid == 0)
	{
		execute_bin(cmd);
		exit(g_shell->exit_status);
	}
	else
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFEXITED(cmd->status))
			g_shell->exit_status = WEXITSTATUS(cmd->status);
		else if (WIFSIGNALED(cmd->status))
		{
			sig_code = WTERMSIG(cmd->status);
			if (sig_code == SIGTERM)
				ft_printf("Terminated: 15\n");
			else if (sig_code == SIGKILL)
				ft_printf("Killed: 9\n");
			g_shell->exit_status = sig_code + 128;
		}
		else if (WIFSTOPPED(cmd->status))
		{
			printf("hello\n");
			g_shell->exit_status = WSTOPSIG(cmd->status) + 128;
		}
	}
}

void	one_cmd(t_cmd *cmd, t_cmd **head)
{
	int res;
	
	res = make_redirections(cmd);
	if (res == ERROR_EXIT)
		return ;
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd, head);
	else
		execute_one_bin(cmd);
	restaure_fds(cmd);
}
