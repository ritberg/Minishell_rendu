/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:52 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/03 11:56:53 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	init_fd_pipe(int **fd_pipe, int nb_cmds)
{
	int	i;

	i = 0;
	fd_pipe = ft_calloc(nb_cmds, sizeof(int *));
	if (!fd_pipe)
	{
		//erreur
		return (0);
	}
	while (i < nb_cmds)
	{
		fd_pipe[i] = ft_calloc(2, sizeof(int));
		if (fd_pipe[i])
		{
			//free fd_pipe
			//message d'erreur
			return (0);
		}
		i++;
	}
	return (1);
}
static void	exec_bin(t_cmd *cmd)
{
	int	sig_code;

	sig_code = 0;
	execute_bin(cmd);
	exit(g_shell->exit_status);
}


int ft_exe(int save_fdin, t_cmd *cmd, t_cmd **head)
{
	int res;

	dup2(save_fdin, STDIN_FILENO);
	close(save_fdin);
	res = make_redirections(cmd);
	if (res == ERROR_EXIT)
		return (0);
	if (!cmd->cmd)
		return (1);
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd, head);
	else
		exec_bin(cmd);
	restaure_fds(cmd);
	return (1);
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
			ft_exe(save_fdin, cmd, head);
			exit(g_shell->exit_status);
		} 
		else 
		{
			close(fd_pipe[1]);
			close(save_fdin);
			save_fdin = fd_pipe[0]; 
		}
		cmd = cmd->next;
	}
	cmd = *head;
	while (cmd)
	{
		waitpid(cmd->pid, &cmd->status, WUNTRACED);
		if (WIFEXITED(cmd->status))
		{
			g_shell->exit_status = cmd->status % 256;
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
