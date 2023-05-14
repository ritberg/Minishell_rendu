/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:26:55 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/14 17:49:22 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pwd(t_cmd *cmd)
{
	char	*cwd;

//	cmd = malloc(sizeof(t_cmd));
//	if (!cmd)
//		return (0);
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1); // 1 - testing with stdout
	ft_putstr_fd("\n", cmd->fdout);
	free(cwd);
	return (1);
}
/*
int	echo(t_cmd *cmd)
{
	if (!cmd->option)   // if cmd->option is a *char
		ft_putstr_fd("\n", cmd->fdout);
	ft_putstr_fd(cmd->cmd, cmd->fdout); // if cmd->cmd is a *char
	return (1);
}
*/
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

