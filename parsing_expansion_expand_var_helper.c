/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_expand_var_helper.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:28:54 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/18 10:07:59 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	replace_content(t_token *tmp, char *s)
{
	free(tmp->content);
	tmp->content = NULL;
	tmp->content = ft_strdup(s);
	if (!tmp->content)
	{
		malloc_error_print_message("ft_strdup failed");
		return (ERROR_EXIT);
	}
	return (1);
}

int	check_var_exist(t_token *tmp)
{
	if (ft_strncmp(&tmp->content[1], "?", 1) == 0)
	{
		return (replace_content(tmp, ft_itoa(g_shell->exit_status)));
	}
	else if (ft_strncmp(g_shell->env->var_name, &tmp->content[1], \
				ft_strlen(tmp->content)) == 0)
	{
		return (replace_content(tmp, g_shell->env->var_value));
	}
	return (0);
}

int	size_var(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && is_white_space(s[i]))
		i++;
	while (s[i] && !is_white_space(s[i]))
	{
		count++;
		i++;
	}
	return (count);
}
