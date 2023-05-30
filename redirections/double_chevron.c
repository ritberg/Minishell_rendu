/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:37:46 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/30 16:03:19 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sigint(int key)
{
	(void)key;
	exit(0);
}

void sig_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint);
}

void	child_process(char *key_word)
{
	char *doc  = "here_doc";
	char *line;
	char *tmp1;
	char *tmp2;
	int	fd;
	
	line = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	sig_handler();	
	fd = open(doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = readline(MAG"> "RESET);
	while (ft_strncmp(line, key_word, ft_strlen(key_word)) != 0)
	{
		if (tmp2)
			tmp1 = ft_strjoin(tmp2, "\n");
		else
			tmp1 = ft_strjoin(line, "\n");
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline(MAG"> "RESET);
		if (!line)
			break;
		if (tmp2)
		{
			free(tmp2);
			tmp2 = NULL;
		}
		tmp2 = ft_strjoin(tmp1, line);
		free(tmp1);
		tmp1 = NULL;
	}
	if (!line)
		printf("%s\n", tmp1);
	else
	{
		free(line);
		printf("%s\n", tmp2);
	}
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
		waitpid(pid, &status, 0);
	return (1);
}
