/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:20:24 by mdanchev          #+#    #+#             */
/*   Updated: 2023/06/04 14:47:16 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	child_process(char *key_word)
{
	char	*line;
	int		fd;

	line = NULL;	
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		exit(1);
	}
	while (1)
	{
		if (line)
			free(line);
		line = readline(MAG"> "RESET);
		if (!line)
			break ;
		else if (ft_strncmp(key_word, line, ft_strlen(key_word) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(fd,"%s\n", line);
	}
	close(fd);
}

static int	here_doc(char *key_word)
{
	int	pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		here_doc_signal_handler();
		child_process(key_word);
		parent_signal_handler();
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			g_shell->exit_status = 1;
			return (0);
		}
	}
	return (1);
}

int	redir_fdin(t_cmd *cmd, char *redir_op, char *file_path)
{
	if (cmd->save_fdin != -1 || cmd->ffd_in != -1)
		restaure_fds(cmd);
	if (ft_strlen(redir_op) == 1)
		cmd->ffd_in = open(file_path, O_RDONLY);
	else
	{
		if (!here_doc(file_path))
			return (0);
		cmd->ffd_in = open(".here_doc", O_RDONLY);
	}
	cmd->save_fdin = dup(STDIN_FILENO);
	if (cmd->ffd_in < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		g_shell->exit_status = 1;
		return (0);
	}
	dup2(cmd->ffd_in, STDIN_FILENO);
	close(cmd->ffd_in);
	cmd->ffd_in = -1;
	return (1);
}

int	redir_fdout(t_cmd *cmd, char *redir_op, char *file_path)
{
	if (cmd->save_fdout != -1 || cmd->ffd_out != -1)
		restaure_fds(cmd);
	cmd->save_fdout = dup(STDOUT_FILENO);
	if (ft_strlen(redir_op) == 1)
		cmd->ffd_out = open(file_path, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
	else
		cmd->ffd_out = open(file_path, O_WRONLY | O_CREAT | O_APPEND,  0644);
	if (cmd->ffd_out < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		g_shell->exit_status = 1;
		return (0);
	}
	dup2(cmd->ffd_out, STDOUT_FILENO);
	close(cmd->ffd_out);
	cmd->ffd_out = -1;
	return (1);
}
