/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/22 12:39:48 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	exec_bin(t_cmd *cmd, t_bin *bin)
{
	int	status;
	int	res = 0;

	status = 0;
	bin->child = fork();
	if (!cmd->cmd)
		return ;
	if (bin->child < 0)
		return (perror("Fork: "));
	if (bin->child == 0)
	{
  		 res = execve(bin->cmd, cmd->cmd, g_shell->save_env);
		 ft_dprintf(2, "minishell: %s\n", strerror(errno));
		 if (res < 0)
		 {
			 printf("res = %d\n", res);
			 exit(127);
		 }
		 exit (0);
	}

	else
		waitpid(bin->child, &status, 0);
	g_shell->exit_status = WEXITSTATUS(status);
}

void	check_then_execute(t_token *token, t_cmd *cmd)
{
	t_bin	*bin;

	bin = malloc(sizeof(t_bin));
	g_shell->save_env = copy_env_tab(g_shell->env);
	if (token && token->id == WORD)
	{
		if (cmd_is_bin(token, bin))
			exec_bin(cmd, bin);
	//	if (cmd_is_builtin(token))
	//		exec_builtin(token);
	//	if (cmd_is_fd(token))
	//		open_fd(token);
	}
}
