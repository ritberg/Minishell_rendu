/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:56:41 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/22 09:57:54 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

//extern int g_exit_status;



int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	char	*line;
	t_token	*token;

	if (!init_shell(envp))
		return (1);
	if (sig_handler() == -1) // a modifier apres le parsing
		return (1);
	while (1)
	{
		line = NULL;
		line = readline(BLU_2"minishell$ "RESET);
		if (!line) // s'il y a une erreur de malloc ou CNTR+D
    	{
			rl_clear_history();
			break ;
    	}
		if (line[0])
			add_history(line);

		/* TEST BUILTIN PWD */
		t_cmd	*cmd;
		if (ft_strncmp(line, "pwd", 3) == 0)
		{
			cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				return (0);
			_pwd(cmd);
		}

		token = parsing(line);
//		printf("EXIT STATUS %d\n", g_shell->exit_status);
		g_shell->exit_status = 0;
		free_token(&token);
	}
	free_shell();
	return (0);
}
