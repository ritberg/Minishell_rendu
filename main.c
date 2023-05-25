/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:56:41 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/24 16:25:11 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

//extern int g_exit_status;

char	*readline_routine(void)
{
	char	*line;
	
	line = NULL;
	line = readline(BLU_2"minishell$ "RESET);
	if (!line) // s'il y a une erreur de malloc ou CNTR+D
	{
		rl_clear_history();
		return (NULL) ;
	}
	if (line[0])
		add_history(line);
	return (line);
}

void	print_cmd(t_cmd **head)
{
	t_cmd	*ptr;
	int	i = 0;
	int	j = 0;

	if (!head || !*head)
		return ;
	ptr = *head;
	while (ptr)
	{
		if (ptr->cmd)
		{
			while(ptr->cmd[j])
			{
				ft_printf("cmd[%d] = ", i);
				ft_printf("%s\n", ptr->cmd[j]);
				j++;
			}
		}
		j = 0;
		if (ptr->redir)
		{
			while (ptr->redir[j])
			{
				ft_printf("redir[%d] = ", i);
				ft_printf("%s\n", ptr->redir[j]);
				j++;
			}
		}
		if (ptr->path)
		{
			ft_printf("path[%d] = ", i);
			ft_printf("%s\n", ptr->path);
		}
		j = 0;
		i++;
		ptr = ptr->next;
	}
}


int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

	if (!init_shell(envp))
		return (1);
	if (sig_handler() == -1) // a modifier apres le parsing
		return (1);
	while (1)
	{
		line = readline_routine();
		if (!line)
			break ;
		token = parsing(line);
		cmd = cmd_linked_list(&token);
//		print_cmd(&cmd);
		if (g_shell->error_exit == 1)
		{
			free_shell();
			return (1);
		}
		execution(&cmd);
		free_cmd(&cmd);
	}
	free_shell();
	printf("exit\n");
	return (0);
}
