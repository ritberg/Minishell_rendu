/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:52 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/03 14:50:29 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


void ft_exe(int i, int save_fdin, t_cmd *cmd, t_cmd **head)
{
	int res;

	if (i != 0)
	{
		dup2(save_fdin, STDIN_FILENO);
		close(save_fdin);
	}
	res = make_redirections(cmd);
	if (res == ERROR_EXIT)
		return ;
	if (!cmd->cmd)
		return ;
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd, head);
	else
		execute_bin(cmd);
	restaure_fds(cmd);
	return ;
}
	

void	pipex(t_cmd **head, int nb_cmds)
{
	(void)nb_cmds;
	int	fd_pipe[2];
	int	save_fdin;
	t_cmd *cmd;
	int	i;

	i = 0;
	if (!head || !*head)
		return ;
	cmd = *head;
	while (cmd)
	{
		pipe(fd_pipe);
		cmd->pid= fork();
		child_signal_handler(cmd->pid);
		if (cmd->pid == 0)
		{
			if (cmd->next != NULL)
				dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_exe(i, save_fdin, cmd, head);
			exit(g_shell->exit_status);
		} 
		else 
		{
			close(fd_pipe[1]);
			close(save_fdin);
			save_fdin = fd_pipe[0]; 
		}
		cmd = cmd->next;
		i++;
	}
	cmd = *head;
	while (cmd)
	{
		waitpid(cmd->pid, &cmd->status, 0);
	//	printf("cmd status = %d\n", cmd->status);
		if (WIFEXITED(cmd->status))
		{
	//		printf("normal exit\n");
			g_shell->exit_status = cmd->status / 256;
		}
		cmd = cmd->next;
	}
	cmd = *head;
	close(save_fdin);
}

	/*
	else
	{
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
	}*/
