/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:53:08 by mmakarov          #+#    #+#             */
/*   Updated: 2023/06/09 14:16:43 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	child_process_helper(char *key_word, int flag, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
			free(line);
		line = readline("> ");
		if (!line)
			break ;
		else if ((!flag && \
					ft_strncmp(key_word, line, ft_strlen(key_word) + 1) == 0))
		{
			free(line);
			break ;
		}
		else if (flag && ft_strncmp(line, "\0", 1) == 0)
		{
			free(line);
			break ;
		}
		ft_dprintf(fd, "%s\n", line);
	}
}

static void	child_process(char *key_word, int j)
{
	char	*file;
	int		fd;
	int		flag;

	flag = 0;
	if (ft_strncmp(key_word, "\'\'", 3) == 0 || \
			ft_strncmp(key_word, "\"\"", 3) == 0)
	{
		flag = 1;
	}
	file = ft_strjoin(".here_doc", ft_itoa(j));
	if (access(file, F_OK))
		unlink(file);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		exit(1);
	}
	child_process_helper(key_word, flag, fd);
	close(fd);
}

static int	write_in_heredoc(char *key_word, int j)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		here_doc_signal_handler();
		child_process(key_word, j);
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

int	here_doc(t_token **head)
{
	t_token	*token;
	int		i;

	i = 0;
	token = *head;
	while (token)
	{
		if (token->id == PIPELINE)
			i++;
		if (token->id == HERE_DOC)
		{
			token = token->next;
			write_in_heredoc(token->content, i);
		}
		token = token->next;
	}
	return (0);
}
