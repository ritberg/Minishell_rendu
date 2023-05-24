/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:36:56 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/23 10:28:51 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	get_cmd_size(t_token **token)
{
	t_token	*ptr;
	int		i;

	i = 0;
	ptr = *token;
	if (!token || !*token)
		return (-1);
	while (ptr && ptr->id != PIPELINE)
	{
		if (ptr->id == L_CHEVRON || ptr->id == R_CHEVRON || \
				ptr->id == APPEND || ptr->id == HERE_DOC)
		{
			ptr = ptr->next->next;
		}
		else
		{
			i++;
			ptr = ptr->next;
		}
	}
	return (i);
}

static void	copy_cmd(t_token **token, t_cmd *cmd)
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
			cmd->cmd[i] = ft_strdup(ptr->content);
			ptr = ptr->next;
			i++;
		}
	}
	cmd->cmd[i] = NULL;
}

void	create_cmd(t_token **token, t_cmd *cmd)
{
	int	i;

	i = get_cmd_size(token);
	if (i == -1)
		return ;
	cmd->cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd->cmd)
	{
		malloc_error_print_message(strerror(errno));
		return ;
	}
	copy_cmd(token, cmd);
}

