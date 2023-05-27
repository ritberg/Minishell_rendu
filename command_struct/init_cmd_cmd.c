/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:36:56 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/27 20:40:14 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	is_dir(char *s, t_cmd *cmd, int i)
{
	struct stat buf;

	if (stat(s, &buf) == 0)
	{
		if(S_ISDIR(buf.st_mode))
		{
			cmd->path = ft_strdup(s);
			cmd->cmd[i] = NULL;
			return (1);
		}
	}
	return (0);
}

static int	extract_cmd_path(char *s, t_cmd *cmd, int i)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (is_dir(s, cmd, i))
		return (1);
	while (s[end])
		end++;
	start = end--;
	while (s[start] != '/')
		start--;
	cmd->cmd[i] = ft_substr(s, start + 1, end - start);
	if (!cmd->cmd[i])
	{
		malloc_error_print_message("ft_substr failed");
		return (0);
	}
	cmd->path = ft_strdup(s);
	if (!cmd->path)
	{
		malloc_error_print_message("ft_strdup failed");
		return (0);
	}
	return (1);
}

static int	check_cmd_is_path(char *s, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
		{
			cmd->cmd_is_path_fg = true;
			return (1);
		}
		i++;
	}
	cmd->cmd_is_path_fg = false;
	return (0);
}

static int	copy_cmd_helper(t_token *ptr, t_cmd *cmd, int i)
{
	if (i == 0 && check_cmd_is_path(ptr->content, cmd))
	{
		if (!extract_cmd_path(ptr->content, cmd, i))
			return (0);
	}
	else
	{
		cmd->cmd[i] = ft_strdup(ptr->content);
		if (!cmd->cmd[i])
		{
			malloc_error_print_message("ft_strdup failed");
			return (0);
		}
	}
	return (1);
}

/*
 * copy_cmd() function
 *
 * GOAL: This function copies the commande in cmd->cmd.
 * 
 * Returned values: 
 * 		If a malloc error occurs, the function returns 0.
 * 		Else, it returns 1 for success.
 *
 * Procedure:
 * 	- A command can only be a token that has been marked as WORD.
 * 	- The first word in the sequence is the command name,
 * 	  and all words that follow are command arguments.
 * 	- A redirection operato takes always one argument. So if the current 
 * 	  token is marked as a metacharacter,we move two tokens forward.
 * 	  (ptr = ptr->next->next)
 * 	- copy_cmd_helper() is called. This function does:
 * 		 - If the current token is the first encountered token marked as WORD,
 *  	   the function checks if the command is a path (check_cmd_is_path()).
 * 		   If true, extract_cmd_path() duplicates the path in cmd->path 
 * 	  	   (ex. /bin/ls),and the command name in cmd->cmd (ex. ls).
 * 	       Then it set the flag cmd_is_path_fg to true.
 * 		- Else, a simple strdup is made.
 */

static int	copy_cmd(t_token **token, t_cmd *cmd)
{
	t_token	*ptr;
	int		i;

	ptr = *token;
	i = 0;
	while (ptr && ptr->id != PIPELINE)
	{
		if (ptr->id == L_CHEVRON || ptr->id == R_CHEVRON || \
				ptr->id == APPEND || ptr->id == HERE_DOC)
			ptr = ptr->next->next;
		else
		{
			if (!copy_cmd_helper(ptr, cmd, i))
					return (0);
			ptr = ptr->next;
			i++;
		}
	}
	cmd->cmd[i] = NULL;
	return (1);
}
/*
 * create_cmd() function
 * GOAL: create char **cmd of the t_cmd cmd structure.
 *
 * Returned values:
 * 	-> 1 for succes
 * 	-> 0 for malloc failure
 *
 * Procedure:
 * 1. Get the size the we need to malloc with get_cmd_size() function
 * 		-> if size == 0 -> there is no command
 * 		-> cmd->cmd is NULL since t_cmd *cmd was generated with calloc
 * 		-> so we simply return
 * 2. Malloc size + 1 for the NULL
 * 3. Copy the command in the cmd->cmd with copy_cmd() function
 */

int	create_cmd(t_token **token, t_cmd *cmd)
{
	int	i;
	int	res;

	i = get_cmd_size(token);
	if (i == 0)
		return (1);
	cmd->cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd->cmd)
	{
		malloc_error_print_message(strerror(errno));
		return (0);
	}
	res = copy_cmd(token, cmd);
	if (!res)
		return (0);
	return (1);
}
