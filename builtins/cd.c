/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:39:56 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/24 14:10:38 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


static char	*get_env(char *var_name)
{
	t_env	*env;

	env = g_shell->env;
	while (env != NULL)
	{
		if (ft_strncmp(env->var_name, var_name, ft_strlen(var_name)) == 0)
			return (env->var_value);
		env = env->next;
	}
	return (NULL);
}

static void	print_chdir_error(char *arg, char *err)
{
	ft_dprintf(2, "minishell: cd: %s: ", arg);
	ft_dprintf(2, "%s\n", err);
	g_shell->exit_status = 1;
}

static int	change_dir(char *oldpwd, char *path)
{
	int	res;

	res = chdir(path);
	if (res == -1)
	{
		free(oldpwd);
		print_chdir_error(path, strerror(errno));
		return 0;
	}
	g_shell->exit_status = 0;
	return (1);
}

void	_cd(t_cmd *cmd)
{
	int	res;
	char *oldpwd;
	char *pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		print_getcwd_error(strerror(errno));
		return ;
	}
	if (size_tab2d(cmd->cmd) == 1)
		res = change_dir(oldpwd, get_env("HOME"));
	else
		res = change_dir(oldpwd, cmd->cmd[1]);
	if (!res)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(oldpwd);
		print_getcwd_error(strerror(errno));
		return ;
	}
	change_env(oldpwd, pwd, cmd);
}
