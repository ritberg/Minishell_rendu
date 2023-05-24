/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/23 10:00:49 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	execution_bin(t_cmd *cmd, t_bin *bin)
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
		 if (res < 0)
		 {
			 ft_dprintf(2, "minishell: %s\n", strerror(errno));
			 printf("res = %d\n", res);
			 exit(127);
		 }
		 exit (0);
	}

	else
		waitpid(bin->child, &status, 0);
	g_shell->exit_status = WEXITSTATUS(status);
}



void	builtin(t_bin *bin, t_cmd *cmd)
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
		if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0 /*&& taille 1*/ )
			_pwd(cmd);
		else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
			_echo(cmd);
		else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
			_env(g_shell->env);
		else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
			exit (0);
		 if (res < 0)
		 {
			 ft_dprintf(2, "minishell: %s\n", strerror(errno));
			 exit(127);
		 }
		 exit (0);
	}

	else
		waitpid(bin->child, &status, 0);
	g_shell->exit_status = WEXITSTATUS(status) % 256;
}

void	check_then_execute(t_token *token, t_cmd **cmd)
{
	t_bin	*bin;
	t_cmd *ptr;

	ptr = *cmd;
	bin = malloc(sizeof(t_bin));
	g_shell->save_env = copy_env_tab(g_shell->env);
	if (token && token->id == WORD)
	{
		if (ft_strncmp(token->content, "exit", 5) == 0)
		{
			printf("exit\n");
			exit (0);
		}
		else if (cmd_is_builtin(token) == 1)
		{
			builtin(bin, *cmd);
			return ;
		}
		else if (cmd_is_bin(token, bin))
		{
			execution_bin(*cmd, bin);
			return ;
		}
	//	if (cmd_is_fd(token))
	//		open_fd(token);
	}
}
