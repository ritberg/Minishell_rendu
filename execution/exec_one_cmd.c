/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:08:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/03 13:01:03 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_signal_message(int sig_code)
{
	if (sig_code == SIGTERM)
	{
		g_shell->terminated++;
		ft_printf("[%d]\t Terminated: 15\n", g_shell->terminated);
	}
	else if (sig_code == SIGQUIT)
	{
		printf(" main QUIT: 3\n");
	}
}

static void	execute_one_bin(t_cmd *cmd)
{
	int	sig_code;
	sig_code = 0;
	cmd->pid = fork();
	child_signal_handler(g_shell->pid);
	if (cmd->pid < 0)
		return (perror("Fork: "));
	if (cmd->pid == 0)
	{
		execute_bin(cmd);
		cmd->status = g_shell->exit_status;
		exit(g_shell->exit_status);
	}
	else
	{
		g_shell->pid = cmd->pid;
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFSIGNALED(cmd->status))
		{
			print_signal_message(WTERMSIG(cmd->status));
			g_shell->exit_status = WTERMSIG(cmd->status) + 128;
		}
		else if (WIFEXITED(cmd->status))
		{
			if (g_shell->exit_status == 146)
				ft_printf("\t\t\t%s\n", cmd->cmd[0]);
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
