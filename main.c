/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:56:41 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/22 15:59:46 by mdanchev         ###   lausanne.ch       */
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
///		if (g_shell->exit_status > 0)
//			break ;
		cmd = init_cmd(&token);
//		if (g_shell->exit_status > 0)
//			break ;
		check_then_execute(token, cmd);
//		printf ("exit status = %d\n", g_shell->exit_status);
		//g_shell->exit_status = 0;
		free_token(&token);
		free_cmd(&cmd);
	}
	free_shell();
	return (0);
}
