/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:26:55 by mmakarov          #+#    #+#             */
/*   Updated: 2023/05/12 19:20:42 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_cmd *cmd)
{
	char	*cwd;

//	cmd = malloc(sizeof(t_cmd));
//	if (!cmd)
//		return (0);
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, 1); // testing with strdout
	ft_putstr_fd("\n", cmd->fdout);
	free(cwd);
	return (1);
}
