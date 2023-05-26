/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:39:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/25 10:19:32 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*void	execution(t_cmd **cmd)
{
	int		i;
	
	g_shell->save_env = copy_env_tab(g_shell->env);
	i = check_for_pipes(cmd);
	if (i == 0 && ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		free_cmd(cmd);
		free_shell();
		printf("exit\n");
		exit (0);
	}
	else if ((*cmd)->cmd_is_path_fg == false && cmd_is_builtin(cmd) == 1)
	{
		execution_builtin(*cmd);
		return ;
	}
	else if (cmd_is_bin(cmd))
	{
		execution_bin(*cmd);
		return ;
	}
//	if (cmd_is_fd(token))
//		open_fd(token);
}*/


/*
void	execute_pipes(t_cmd **head, int nb_pipes)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (perror("Fork: "));
	if (cmd->pid == 0)
	{
		check_then_execute(cmd);
		exit(0);
	}
	else
	{
		waitpid(cmd->pid, &cmd->status, 0);
		g_shell->exit_status = WEXITSTATUS(cmd->status);
		printf("end\n");
	}

}
*/

void	execute_builtin(t_cmd *cmd, t_cmd **head)
{
	if (ft_strncmp(cmd->cmd[0], "exit", 6) == 0)
		ft_exit(&cmd);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		_pwd();
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		_echo(cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		_env(cmd, g_shell->env);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		_cd(cmd, head);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		_export(cmd, head);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		_unset(cmd);
	return ;
}

void	one_cmd(t_cmd *cmd, t_cmd **head)
{
	if (cmd_is_builtin(cmd->cmd[0]) && cmd->cmd_is_path_fg == false)
		execute_builtin(cmd, head);
//	else if (cmd_is_bin(cmd->cmd[0]))
//		execute_bin(cmd);
}

int	check_for_pipes(t_cmd **head)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = *head;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}	

void	execution(t_cmd **head)
{
	t_cmd	*cmd;
	int		nb_pipes;

	cmd = *head;
	if (!head || !*head)
		return ;
	nb_pipes = check_for_pipes(head);
	if (nb_pipes == 1)
		one_cmd(cmd, head);
//	else
//		multiple_cmds(head, nb_pipes);
}


/*
void	execution_bin(t_cmd **cmd)
{
	int	status;
	int	res = 0;

	status = 0;
	(*cmd)->pid = fork();
	if (!cmd->cmd)
		return ;
	if ((*cmd)->pid < 0)
		return (perror("Fork: "));
	if ((*cmd)->pid == 0)
	{
		if (cmd->cmd_is_path_fg == true)
		{
			 res = execve(cmd->path, (*cmd)->cmd, g_shell->save_env);
		}
		else
		{
			 res = execve((*cmd)->path, (*cmd)->cmd, g_shell->save_env);
		}
		 if (res < 0)
		 {
			 ft_dprintf(2, "minishell: %s\n", strerror(errno));
			 printf("res = %d\n", res);
			 exit(127);
		 }
		 exit (0);
	}

	else
		waitpid((*cmd)->pid, &status, 0);
	g_shell->exit_status = WEXITSTATUS(status);
}



void	execution_builtin(t_bin *bin, t_cmd *cmd)
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
		if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0 )
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



void	execution(t_cmd **cmd)
{
	int		i;
	
	i = check_for_pipes(cmd);
	if (i == 0 && ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		free_cmd(cmd);
		free_shell();
		printf("exit\n");
		exit (0);
	}
	else if ((*cmd)->cmd_is_path_fg == false && cmd_is_builtin(cmd) == 1)
	{
		execution_builtin(*cmd);
		return ;
	}
	else if (cmd_is_bin(cmd))
	{
		execution_bin(*cmd);
		return ;
	}
//	if (cmd_is_fd(token))
//		open_fd(token);
}*/

