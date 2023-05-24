/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:54:50 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/23 10:33:09 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	cmd_backadd(t_cmd **head, t_cmd *new)
{
	t_cmd	*ptr;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	ptr = *head;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	ptr->next = new;
}

int	get_redir_size(t_token *ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr->id != PIPELINE)
	{
		if (ptr->id == L_CHEVRON || ptr->id == R_CHEVRON || \
				ptr->id == APPEND || ptr->id == HERE_DOC)
			i = i + 2;
		ptr = ptr->next;
	}
	return (i);
}

void	copy_redir(t_token **token, t_cmd *cmd)
{
	t_token	*ptr;
	int		i;

	ptr = *token;
	i = 0;
	while (ptr && ptr->id != PIPELINE)
	{
		if (ptr->id == L_CHEVRON || ptr->id == R_CHEVRON || \
				ptr->id == APPEND || ptr->id == HERE_DOC)
		{
			cmd->redir[i] = ft_strdup(ptr->content);
			if (!cmd->redir[i])
			{
				malloc_error_print_message("ft_strdup failed");
				return ;
			}
			i++;
			ptr = ptr->next;
			cmd->redir[i] = ft_strdup(ptr->content);
			if (!cmd->redir[i])
			{
				malloc_error_print_message("ft_strdup failed");
				return ;
			}
			i++;
		}
		ptr = ptr->next;
	}
}

int	create_redir(t_token **token, t_cmd *cmd)
{
	t_token	*ptr;
	int		i;

	ptr = *token;
	i = get_redir_size(ptr);
	if (i == 0)
	{
		cmd->redir = NULL;
		return (1);
	}
	cmd->redir = ft_calloc(i + 1, sizeof(char *));
	if (!cmd->redir)
	{
		malloc_error_print_message("ft_calloc failed");
		return (0);
	}
	copy_redir(token, cmd);
	return (1);
}

t_cmd *init_cmd(t_token **token)
{
	t_cmd	*cmd;
	int		res;

	res = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		malloc_error_print_message("ft_calloc failed");
		return (NULL);
	}
	create_cmd(token, cmd);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	res = create_redir(token, cmd);
	if (res == -1)
	{
		free_cmd(&cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*cmd_linked_list(t_token **token)
{
	t_cmd *head;
	t_cmd *new;
	t_token	*ptr;

	ptr = *token;
	head = NULL;
	head = init_cmd(&ptr);
	if (!head)
		return (NULL);
	while (ptr && ptr->id != PIPELINE)
		ptr = ptr->next;
	while (ptr)
	{
		if (ptr->id != PIPELINE)
		{
			new = init_cmd(&ptr);
			if (!new)
			{
				free_cmd(&head);
				return (NULL);
			}
			cmd_backadd(&head, new);
			while (ptr && ptr->id != PIPELINE)
				ptr = ptr->next;
		}
		else 
			ptr = ptr->next;
	}
	return (head);
}

