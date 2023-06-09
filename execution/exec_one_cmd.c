/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:08:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/09 10:07:15 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	print_signal_message(int sig_code)
{
	if (sig_code == SIGTERM)
	{
		g_shell->terminated++;
		ft_printf("[%d]\t Terminated: 15\n", g_shell->terminated);
	}
	else if (sig_code == SIGQUIT)
		ft_printf("QUIT: 3\n");
	else if (sig_code == SIGINT)
		ft_printf("\n");
	else if (sig_code == SIGKILL)
		ft_printf("Killed: 9 \n");
}

static void	execute_one_bin(t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("minishell: fork: "));
	if (cmd->pid == 0)
	{
		child_signal_handler();
		execute_bin(cmd);
		cmd->status = g_shell->exit_status;
		exit(g_shell->exit_status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFSIGNALED(cmd->status))
		{
			print_signal_message(WTERMSIG(cmd->status));
			g_shell->exit_status = WTERMSIG(cmd->status) + 128;
		}
		else if (WIFEXITED(cmd->status))
			g_shell->exit_status = WEXITSTATUS(cmd->status);
	}
}

void	one_cmd(t_cmd *cmd)
{
	int	res;

	res = make_redirections(cmd, 0);
	if (!res || !cmd->cmd)
	{
		restaure_fds(cmd, 0);
		return ;
	}
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd);
	else
		execute_one_bin(cmd);
	restaure_fds(cmd, 0);
}
