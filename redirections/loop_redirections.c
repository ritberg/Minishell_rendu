/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:19:00 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/08 17:23:11 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	restaure_fds(t_cmd *cmd, int i)
{
	char *file;

	file = ft_strjoin(".here_doc", ft_itoa(i));
	if (!file)									// A SUPPRIMER
		printf("error restauring here doc\n"); // A SUPPRIMER
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
	if (!file)
		return ;
	if (access(file, F_OK) == 0)
		unlink(file);
}

int	make_redirections(t_cmd *cmd, int j)
{
	int	i;

	i = 0;
	if (!cmd->redir)
	{
		return (1);
	}
	while (cmd->redir[i])
	{
	//	printf("cmd redir = %s\n", cmd->redir[i]);
		if (ft_strncmp(cmd->redir[i], ">", 2) == 0 || \
			ft_strncmp(cmd->redir[i], ">>", 3) == 0)
		{
			if (!redir_fdout(cmd, cmd->redir[i], cmd->redir[i + 1]))
				return (0);
			i++;
		}
		else if (ft_strncmp(cmd->redir[i], "<", 2) == 0)
		{
			if (!redir_fdin(cmd, cmd->redir[i], cmd->redir[i + 1], j))
				return (0);
			i++;
		}
		else if (ft_strncmp(cmd->redir[i], "<<", 3) == 0)
		{
			if (!redir_fdin(cmd, cmd->redir[i], NULL, j))
				return (0);
			if (cmd->redir[i + 1])
				i++;
			i++;
		}
		else
			i++;
	}
	return (1);
}
