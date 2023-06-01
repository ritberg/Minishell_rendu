/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:08:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/01 17:26:47 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	test(int code)
{
	(void)code;
	printf("sig tstp\n");
}

static void	execute_one_bin(t_cmd *cmd)
{
	int	sig_code;
	sig_code = 0;
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("Fork: "));
	if (cmd->pid == 0)
	{
		child_signal_handler(cmd->pid);
		execute_bin(cmd);
		exit(g_shell->exit_status);
	}
	else
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFSIGNALED(cmd->status))
		{
			sig_code = WTERMSIG(cmd->status);
			if (sig_code == SIGINT)
				ft_printf("\n");
			else if (sig_code == SIGTSTP)
				ft_printf("\n");
			else if (sig_code == SIGTERM)
				ft_printf("Terminated: 15\n");
			else if (sig_code == SIGQUIT)
				ft_printf("coucou QUIT: 3\n");
			else if (sig_code == SIGKILL)
				ft_printf("Killed: 9\n");
			g_shell->exit_status = sig_code + 128;
		}
		else if (WIFEXITED(cmd->status))
		{
		//	printf("coucou\n");
		//	printf("status = %d\n", WEXITSTATUS(cmd->status));
			g_shell->exit_status = WEXITSTATUS(cmd->status);
		}
		else if (WIFSTOPPED(cmd->status))
		{
		//	printf("hello\n");
			g_shell->exit_status = WSTOPSIG(cmd->status) + 128;
		}
		parent_signal_handler();
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
