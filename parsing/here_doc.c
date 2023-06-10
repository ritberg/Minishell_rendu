/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:53:08 by mmakarov          #+#    #+#             */
/*   Updated: 2023/06/10 13:42:13 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	helper(char *key_word, int flag, int fd)
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

static char	*create_heredoc_name(int j)
{
	char	*file;
	char	*nb;

	nb = ft_itoa(j);
	if (!nb)
	{
		error_message("ft_itoa failed");
		exit(1);
	}
	file = ft_strjoin(".here_doc", nb);
	free(nb);
	if (!file)
	{
		error_message("ft_strjoin failed");
		exit(1);
	}
	return (file);
}

static void	write_in_heredoc(char *key_word, int j)
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
	file = create_heredoc_name(j);
	if (access(file, F_OK))
		unlink(file);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(file);
		ft_dprintf(2, "minishell: open: %s\n", strerror(errno));
		exit(1);
	}
	helper(key_word, flag, fd);
	close(fd);
}

static int	heredoc_child_process(char *key_word, int j)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		error_message2("fork:", strerror(errno));
		return (0);
	}
	here_doc_signal_handler();
	if (pid == 0)
	{
		write_in_heredoc(key_word, j);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_shell->exit_status = WEXITSTATUS(status);
		g_shell->heredoc_flag = WEXITSTATUS(status);
	}
	return (g_shell->exit_status);
}

int	here_doc(t_token **head)
{
	t_token	*token;
	int		i;
	int		res;

	i = 0;
	token = *head;
	while (token)
	{
		if (token->id == PIPELINE)
			i++;
		if (token->id == HERE_DOC)
		{
			token = token->next;
			res = heredoc_child_process(token->content, i);
			if (res == 1)
			{
				delete_all_heredocs(i);
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}
