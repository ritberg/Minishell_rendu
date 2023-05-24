/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:10:44 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/24 14:12:31 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	change_env_error(char *oldpwd, char *pwd, t_cmd *cmd)
{
	malloc_error_print_message("ft_strdup failed");
	if (oldpwd)
		free (oldpwd);
	if (pwd)
		free (pwd);
	free_cmd(&cmd);
	free_shell();
	exit(1);
}

void	change_env(char *oldpwd, char *pwd, t_cmd *cmd)
{
	t_env	*env;

	env = g_shell->env;
	while (env != NULL)
	{
		if (ft_strncmp(env->var_name, "OLDPWD", 7) == 0)
		{
			free(env->var_value);
			env->var_value = NULL;
			env->var_value = ft_strdup(oldpwd);
			if (!env->var_value)
				change_env_error(oldpwd, pwd, cmd);
		}
		if (ft_strncmp(env->var_name, "PWD", 4) == 0)
		{
			free(env->var_value);
			env->var_value = NULL;
			env->var_value = ft_strdup(pwd);
			if (!env->var_value)
				change_env_error(oldpwd, pwd, cmd);
		}
		env = env->next;
	}
	g_shell->exit_status = 0;
	return (free(oldpwd), free(pwd));
}
