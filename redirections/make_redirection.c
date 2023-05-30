/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:19:00 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/30 15:52:25 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	restaure_fds(t_cmd *cmd)
{
	if (cmd->save_fdout != -1)
	{
		dup2(cmd->save_fdout, STDOUT_FILENO);
		close(cmd->save_fdout);
		cmd->save_fdout = -1;
	}
	if (cmd->save_fdin != -1)
	{
		dup2(cmd->save_fdin, STDIN_FILENO);
		close(cmd->save_fdin);
		cmd->save_fdin = -1;
	}
	
}

int	make_redirections(t_cmd *cmd)
{
	int	i;
	int res;

	i = 0;
	if (!cmd->redir)
		return (0);
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], ">", 2) == 0 || \
			ft_strncmp(cmd->redir[i], ">>", 3) == 0)
		{
			res = redir_fdout(cmd, cmd->redir[i], cmd->redir[i + 1]);
			if (res == ERROR_EXIT)
				return (ERROR_EXIT);
			i++;
		}
		else if (ft_strncmp(cmd->redir[i], "<", 2) == 0)
		{
			res = redir_fdin(cmd, cmd->redir[i + 1]);
			if (res == ERROR_EXIT)
				return (ERROR_EXIT);
			i++;
		}
		else if (ft_strncmp(cmd->redir[i], "<<", 3) == 0)
		{
			i++;
			res = here_doc(cmd, cmd->redir[i]);
			if (res == ERROR_EXIT)
				return (ERROR_EXIT);
		}
		else	
			i++;
	}
	return (res);
}
