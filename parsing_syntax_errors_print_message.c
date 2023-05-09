/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_errors_print_message.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:24:58 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 13:16:13 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
   We print error message, which character has a problem and
   return exit status for syntax errors (258)
*/

void	print_syntax_error_char(char c)
{
	ft_dprintf(2, "minishell: ");
	ft_dprintf(2, "syntax error near unexpected token ");
	ft_dprintf(2, "\'%c\'\n", c);
	g_exit_status = 258;
}

void	print_syntax_error_dchar(char c)
{
	ft_dprintf(2, "minishell: ");
	ft_dprintf(2, "syntax error near unexpected token ");
	ft_dprintf(2, "\'%c%c\'\n", c, c);
	g_exit_status = 258;
}

void	print_syntax_error_str(char *s)
{
	ft_dprintf(2, "minishell: ");
	ft_dprintf(2, "syntax error near unexpected token ");
	ft_dprintf(2, "\'%s\'\n", s);
	g_exit_status = 258;
}
