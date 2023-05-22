/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:54:50 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/22 12:41:27 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_tab2d(char **s)
{
	int	i;

	if (!s || !*s)
		return ;
	i = 0;
	while (s[i])
	{
		free (s[i]);
		i++;
	}
	free (s);
}

void	free_cmd(t_cmd **head)
{
	t_cmd *ptr;
	t_cmd	*tmp;

	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free_tab2d(tmp->cmd);
		free(tmp);
	}
	*head = NULL;
}

t_cmd *init_cmd(t_token **head)
{
	t_cmd	*cmd;
	t_token	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = NULL;
	ptr = *head;
	if (!head || !*head)
		return NULL;
	cmd = ft_calloc(1, sizeof(t_cmd));
	while (ptr && ft_strncmp(ptr->content, "|", 2) != 0)
	{
		i++;
		ptr = ptr->next;
	}
	cmd->cmd = malloc(sizeof(char *) * (i + 1));
	ptr = *head;
	while (j < i)
	{
		cmd->cmd[j] = ft_strdup(ptr->content);
		// FAIRE LES ERREURS DE MALLOC
		ptr = ptr->next;
		j++;
	}
	cmd->cmd[j] = NULL;
	cmd->next = NULL;
	if (!cmd->cmd || !cmd)
		return NULL;
	i = 0;
	printf("\n---CMD---\n");
	while (cmd->cmd[i])
	{
		printf("%s\n", cmd->cmd[i]);
		i++;
	}
	printf("---END---\n");
	return (cmd);

}
