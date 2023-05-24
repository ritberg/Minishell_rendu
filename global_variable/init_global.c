/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:45:47 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/24 14:18:19 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// FOR TESTING PRINTING ENV

void	print_env()
{
	t_env	*ptr;

	ptr = g_shell->env;
	if (!g_shell || !g_shell->env)
		return ;
	while (g_shell->env)
	{
		ft_printf("print_env function: %s\n", g_shell->env->var_name);
		ft_printf("print_env function: %s\n", g_shell->env->var_value);
		g_shell->env = g_shell->env->next;
	}
	g_shell->env = ptr;
}

/* EST_CE QUÓN GARDE SAVE_ENV */ 
void	free_shell(void)
{
	free_env(&g_shell->env);
	if (g_shell->save_env)
		free_tab2d(g_shell->save_env);
//	free_tab(g_shell->save_env);
	if (g_shell)
		free(g_shell);
}

int	shell_no_env()
{
	t_env	*env_no;
	env_no = malloc(sizeof(t_env));
	if (!env_no)
	{
		malloc_error_print_message(strerror(errno));
		return (0);
	}
	env_no->var_name = ft_strdup("SHLVL");
	env_no->var_value = ft_strdup("1");
	env_no->next = NULL;
	g_shell->env = env_no;
	return (1);

}

int	init_shell(char **envp)
{
	g_shell = ft_calloc(1, sizeof(t_shell));
	if (!g_shell)
	{
		ft_dprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (0);
	}
	if (!*envp)
	{
		if (!shell_no_env())
			return (0);
	}
	else
	{
		g_shell->env = get_envp(envp);
		if (!g_shell->env)
			return (free_shell(), 0);
	}
//	g_shell->exit_status = 0;
//	g_shell->error_exit = 0;
	g_shell->save_env = copy_env_tab(g_shell->env); //
//	print_env();
	return (1);
}
