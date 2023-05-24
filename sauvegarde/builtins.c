/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:26:55 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/22 19:18:08 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pwd(t_cmd *cmd)
{
	char	*cwd;
	(void)cmd;
//	cmd = malloc(sizeof(t_cmd));
//	if (!cmd)
//		return (0);
	cwd = getcwd(NULL, 0);
//	ft_putstr_fd(cwd, 1); // 1 - testing with stdout
//	ft_putstr_fd("\n", cmd->fdout);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (1);
}

void	print_echo(char **s, int i)
{
	int size;

	size = i;
	while (s[size])
		size++;
	if (size == i)
		return ;
	while (s[i])
	{
		ft_printf("%s", s[i]);
		if (i != size  - 1)
			ft_printf(" ");
		i++;
	}
}

int	_echo(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[1], "-n", 3) != 0)   // if cmd->option is a *char
	{
		print_echo(cmd->cmd, 1);
		printf("\n");
	}
	else 
		print_echo(cmd->cmd, 2);
	return (1);
}

int	_env(t_env *env)
{
	if (!env)
		return (2);
	while (env != NULL)
	{
		printf("%s=", env->var_name);
		printf("%s\n", env->var_value);
		env = env->next;
	}
	return(1);
}

