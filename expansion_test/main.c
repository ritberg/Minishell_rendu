/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:41:09 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/19 13:13:09 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*g_shell;

//extern int g_exit_status;

// FOR TESTING PRINTING ENV

void	print_env(t_env	**head)
{
	t_env	*ptr;

	ptr = *head;
	if (!head || !*head)
		return ;
	while (ptr)
	{
		ft_printf("print_env function: %s\n", ptr->var_name);
		ft_printf("print_env function: %s\n", ptr->var_value);
		ptr = ptr->next;
	}
}


void	free_shell(void)
{
	free_env(&g_shell->env);
//	free_tab(g_shell->save_env);
	if (g_shell)
		free(g_shell);
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
//		shlvl(g_shell_env);
		return (1);
	}
	g_shell->env = get_envp(envp);
	if (!g_shell->env)
	{
		free_shell();
		ft_dprintf(2, "minishell: malloc: %s\n", strerror(errno));
		return (0);
	}
	g_shell->exit_status = 0;
//	print_env(&g_shell->env);
	return (1);
}


int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)ac;
	char	*line;
	t_token	*token;

	if (!init_shell(envp))
		return (1);
	line = NULL;
//	line = ft_strdup("$SHELL'$SHELL' $a \"$juhtgfd | $USER $SHELL \"$\'coucouc\'wqd\" $\"fwfwef\"\" \"coucou $fd hello\"");
	line = ft_strdup("\"$USER\"");
//	line = ft_strdup("\"\'$$$$US    \' $USER\"");
	printf("LINE = %s\n", line);
	token = parsing(line);
//		printf("EXIT STATUS %d\n", g_shell->exit_status);
	g_shell->exit_status = 0;
	if (token)
		free_token(&token);
	free_shell();
	return (0);
}
