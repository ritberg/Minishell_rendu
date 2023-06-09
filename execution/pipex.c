/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:52 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/09 23:05:46 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	print_signal_message(int sig_code, int *flag)
{
	if (sig_code == SIGTERM)
		ft_printf("Terminated: 15\n");
	else if (sig_code == SIGQUIT)
		ft_printf("Quit: 3\n");
	else if (sig_code == SIGINT)
	{
		*flag = 1;
		ft_printf("\n");
	}
	else if (sig_code == SIGKILL)
		ft_printf("Killed: 9 \n");
}

static void	kill_zombies(t_cmd **head, int flag)
{
	t_cmd	*cmd;
	int		res;

	cmd = *head;
	while (cmd)
	{
		res = waitpid(cmd->pid, &cmd->status, 0);
		if (res >= 0 && WIFSIGNALED(cmd->status) && \
				WTERMSIG(cmd->status) == SIGINT)
		{
			if (flag == 0)
				ft_printf("\n");
		}
		cmd = cmd->next;
	}
}

static void	pipex_get_exit_status(t_cmd *cmd, t_cmd **head)
{
	t_cmd	*last;
	int		flag;

	cmd = *head;
	flag = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		last = cmd;
		cmd = cmd->next;
	}
	if (WIFEXITED(last->status))
		g_shell->exit_status = WEXITSTATUS(last->status);
	else if (WIFSIGNALED(last->status))
	{
		print_signal_message(WTERMSIG(last->status), &flag);
		if (WTERMSIG(last->status) == SIGINT)
		g_shell->exit_status = WTERMSIG(last->status) + 128;
	}
	kill_zombies(head, flag);
}

static void	pipex_helper(int fd_pipe[2], t_cmd *cmd, int i, int *save_fdin)
{
	if (cmd->pid == 0)
	{
		if (cmd->next != NULL)
			dup2(fd_pipe[1], STDOUT_FILENO);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		ft_exe(i, *save_fdin, cmd);
		exit(g_shell->exit_status);
	}
	else
	{
		close(fd_pipe[1]);
		close(*save_fdin);
		*save_fdin = fd_pipe[0];
	}
}

void	pipex(t_cmd **head)
{
	int		fd_pipe[2];
	int		save_fdin;
	t_cmd	*cmd;
	int		i;

	i = 0;
	if (!head || !*head)
		return ;
	cmd = *head;
	while (cmd)
	{
		pipe(fd_pipe);
		cmd->pid = fork();
		pipex_signal_handler();
		pipex_helper(fd_pipe, cmd, i, &save_fdin);
		cmd = cmd->next;
		i++;
	}
	pipex_get_exit_status(cmd, head);
	close(save_fdin);
}

/*
void	pipex(t_cmd **head)
{
	int		fd_pipe[2];
	int		save_fdin;
	t_cmd	*cmd;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!head || !*head)
		return ;
	cmd = *head;
	while (cmd)
	{
		pipe(fd_pipe);
		cmd->pid = fork();
		pipex_signal_handler();
		if (cmd->pid == 0)
		{
			if (cmd->next != NULL)
				dup2(fd_pipe[1], STDOUT_FILENO);
			close(fd_pipe[0]);
			close(fd_pipe[1]);
			ft_exe(i, save_fdin, cmd);
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
	t_cmd	*last;
	while (cmd)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		last = cmd;
		cmd = cmd->next;
	}
	if (WIFEXITED(last->status))
	{
		g_shell->exit_status = WEXITSTATUS(last->status);
	}
	else if (WIFSIGNALED(last->status))
	{
		print_signal_message(WTERMSIG(last->status));
		if (WTERMSIG(last->status) == SIGINT)
			flag = 1;
		g_shell->exit_status = WTERMSIG(last->status) + 128;
	}
	cmd = *head;
	int	res;
	while (cmd)
	{
		res = waitpid(cmd->pid, &cmd->status, 0);
		if (res >= 0 && WIFSIGNALED(cmd->status) && \
				WTERMSIG(cmd->status) == SIGINT && flag == 0)
		{
			print_signal_message(WTERMSIG(cmd->status));
		}
		cmd = cmd->next;
	}
	close(save_fdin);
}*/
