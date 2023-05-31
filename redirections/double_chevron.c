/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:37:46 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/31 11:57:20 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
//rl_on_new_line, rl_replace_line, rl_redisplay,
void	sigint(int key)
{
	(void)key;
	exit(0);
}

void sig_handler(void)
{
	sigset_t set;

	signals_init(&set);	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
}

void	child_process(char *key_word)
{
	char *doc  = ".here_doc";
	char *line;
	int	fd;

	line = NULL;	
	sig_handler();// sa marche pas comme il faut	
	fd = open(doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		exit(0);
	}
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(MAG"> "RESET);
		if (!line)
			break;
		else if (ft_strncmp(line, key_word, ft_strlen(key_word)) == 0)
		{
			free(line);
			break ;
		}
		else 
			ft_dprintf(fd,"%s\n", line);
	}
	close(fd);
	exit(1);
}

int	here_doc(t_cmd *cmd, char *key_word)
{
	(void)cmd;
	int	pid;
	int status;

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
	pid = fork();
	if (pid == 0)
	{
		child_process(key_word);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			g_shell->exit_status = 1;
			return (0);
		}
		else if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			g_shell->exit_status = 1;
			return (0);
		}
		else if(WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM)
		{
			g_shell->exit_status = 1;
			return (0);
		}
	}
	cmd->save_fdin = dup(STDIN_FILENO);
	cmd->ffd_in = open(".here_doc", O_RDONLY);
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
