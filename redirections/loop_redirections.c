/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:19:00 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/09 21:53:49 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	delete_here_doc(int i)
{
	char	*file;
	char	*nb;

	nb = ft_itoa(i);
	if (!nb)
		ft_dprintf(2, "minishell: ft_itoa failed\n");
	file = ft_strjoin(".here_doc", nb);
	if (!file)
		ft_dprintf(2, "minishell: ft_strjoin failed\n");
	if (!file || !nb)
	{
		if (file)
			free(file);
		if (nb)
			free(nb);
		return ;
	}
	if (access(file, F_OK) == 0)
		unlink(file);
	free(file);
	free(nb);
}

void	restaure_fds(t_cmd *cmd, int i)
{
	if (!cmd)
		return ;
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
	delete_here_doc(i);
}

static int	make_redirections_helper(t_cmd *cmd, int j, int i)
{
	if (ft_strncmp(cmd->redir[i], ">", 2) == 0 || \
		ft_strncmp(cmd->redir[i], ">>", 3) == 0)
	{
		if (!redir_fdout(cmd, cmd->redir[i], cmd->redir[i + 1]))
			return (-1);
		i++;
	}
	else if (ft_strncmp(cmd->redir[i], "<", 2) == 0)
	{
		if (!redir_fdin(cmd, cmd->redir[i], cmd->redir[i + 1], j))
			return (-1);
		i++;
	}
	else if (ft_strncmp(cmd->redir[i], "<<", 3) == 0)
	{
		if (!redir_fdin(cmd, cmd->redir[i], NULL, j))
			return (-1);
		if (cmd->redir[i + 1])
			i++;
		i++;
	}
	return (i);
}

int	make_redirections(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	if (!cmd->redir)
		return (1);
	while (cmd->redir[i])
	{
		if (ft_strncmp(cmd->redir[i], ">", 2) == 0 || \
			ft_strncmp(cmd->redir[i], ">>", 3) == 0 || \
			ft_strncmp(cmd->redir[i], "<", 2) == 0 || \
			ft_strncmp(cmd->redir[i], "<<", 3) == 0)
		{
			i = make_redirections_helper(cmd, j, i);
			if (i == -1)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
