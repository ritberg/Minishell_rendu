/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:52 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/08 10:17:57 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
int	check_fdin_redir(t_cmd *cmd)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!cmd->redir)
		return (flag);
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], "<<", 3) == 0 || \
				ft_strncmp(cmd->redir[i], "<", 2) == 0)
		{
			flag = 1;
			break;
		}
		i++;
	}
	return (flag);
}

void	ft_exe(int i, int save_fdin, t_cmd *cmd, t_cmd **head)
{
	int	res;

	if (i != 0 && !check_fdin_redir(cmd))
	{
		dup2(save_fdin, STDIN_FILENO);
		close(save_fdin);
	}
	res = make_redirections(cmd, i);
	if (!res || !cmd->cmd)
	{
		restaure_fds(cmd, i);
		return ;
	}
	if (cmd_is_builtin(cmd->cmd[0]))
		execute_builtin(cmd, head);
	else
		execute_bin(cmd);
	restaure_fds(cmd, i);
	return ;
}

static void	print_signal_message(int sig_code)
{
	if (sig_code == SIGTERM)
	{
		g_shell->terminated++;
		ft_printf("[%d]\t Terminated: 15\n", g_shell->terminated);
	}
	else if (sig_code == SIGQUIT)
		ft_printf("Quit: 3\n");
	else if (sig_code == SIGINT)
		ft_printf("\n");
	else if (sig_code == SIGKILL)
		ft_printf("Killed: 9 \n");
}

void	pipex_handler(int sig_code)
{
	(void)sig_code;
	return ;
}

static void	pipex_signal_handler(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	init_sigset(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGKILL, &act, 0);
	act.sa_handler = pipex_handler;
	sigaction(SIGQUIT, &act, 0);
	sigaction(SIGINT, &act, 0);
}
/*
void	pipex_signals(t_cmd *cmd, t_cmd **head)
{
	t_cmd	*last;
	int		flag;
	int		res;
	
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
		print_signal_message(WTERMSIG(last->status));
		if (WTERMSIG(last->status) == SIGINT)
			flag = 1;
		g_shell->exit_status = WTERMSIG(last->status) + 128;
	}
	cmd = *head;
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
}*/

void	pipex(t_cmd **head)
{
	int	fd_pipe[2];
	int	save_fdin;
	t_cmd *cmd;
	int	i;
	int	flag = 0;

	i = 0;
	if (!head || !*head)
		return ;
	cmd = *head;
	while (cmd)
	{
		pipe(fd_pipe);
		cmd->pid= fork();
		pipex_signal_handler();
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
	t_cmd *last;
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
	int res;
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
}
/*
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
	pipex_signals(cmd, head);
	close(save_fdin);
}*/
