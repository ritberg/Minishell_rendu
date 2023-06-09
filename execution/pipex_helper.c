/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:01:29 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/09 14:01:49 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_fdin_redir(t_cmd *cmd)
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
			break ;
		}
		i++;
	}
	return (flag);
}

void	ft_exe(int i, int save_fdin, t_cmd *cmd)
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
		execute_builtin(cmd);
	else
		execute_bin(cmd);
	restaure_fds(cmd, i);
	return ;
}
