/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:20:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/30 15:52:34 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int	redir_fdin(t_cmd *cmd, char *file_path)
{
	if (cmd->save_fdin != -1)
	{
		dup2(cmd->save_fdin, STDIN_FILENO);
		close(cmd->save_fdin);
		cmd->save_fdin = -1;
	}
	if (cmd->ffd_in != -1)
	{
		close(cmd->ffd_in);
		cmd->ffd_in = -1;
	}
	cmd->save_fdin = dup(STDIN_FILENO);
	cmd->ffd_in = open(file_path, O_RDONLY);
	if (cmd->ffd_in < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		g_shell->exit_status = 1;
		return (ERROR_EXIT);
	}
	dup2(cmd->ffd_in, STDIN_FILENO);
	close(cmd->ffd_in);
	cmd->ffd_in = -1;
	return (1);
}

int	redir_fdout(t_cmd *cmd, char *redir_op, char *file_path)
{
	if (cmd->save_fdout != -1)
	{
		dup2(cmd->save_fdout, STDOUT_FILENO);
		close(cmd->save_fdout);
	}
	if (cmd->ffd_out != -1)
		close(cmd->ffd_out);
	cmd->save_fdout = dup(STDOUT_FILENO);
	if (ft_strlen(redir_op) == 1)
		cmd->ffd_out = open(file_path, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
	else if (ft_strlen(redir_op) == 2)
		cmd->ffd_out = open(file_path, O_WRONLY | O_CREAT | O_APPEND,  0644);
	if (cmd->ffd_out < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		g_shell->exit_status = 1;
		return (ERROR_EXIT);
	}
	dup2(cmd->ffd_out, STDOUT_FILENO);
	close(cmd->ffd_out);
	cmd->ffd_out = -1;
	return (1);
}
