/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing_syntax_errors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:26:12 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 12:26:47 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int g_exit_status = 0;

// Main to test syntax errors

int	main(int ac, char **av)
{
	(void)ac;
	char	*line;
	line = ft_strdup(av[1]);
	syntax_error_check(line);
	printf("exit_status = %d\n", exit_status);
	return (exit_status);
}

