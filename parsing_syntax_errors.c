/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/06 18:00:33 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// int	exit_status = 0;

void	print_error_syntax(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
	exit_status = 258;
}

int	count_quotes(char *s, char *c)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] != c[0])
		i++;
	if (s[i] != c[0])
	{
		print_error_syntax(c);
		return (0);
	}
	return (1);
}

int	count_metachar(char *s, char *c, int num)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] == c[0])
		i++;
	if (i > num)
	{
		print_error_syntax(c);
		return (0);
	}
	while (s[i] && is_blank(s[i]))
		i++;
	if (is_metacharacter(s[i]) || is_operator(s[i]))
	{
		ft_printf_fd(2, "minishell: ");
		ft_printf_fd(2, "syntax error near unexpected token \'%c\'\n", s[i]);
		exit_status = 258;
		return (0);
	}
	return (1);
}

int	syntax_error_check(char *s)
{
	int		i;
	char	c[2];

	c[0] = 0;
	c[1] = 0;
	i = 0;
	while (s[i++])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c[0] = s[i];
			if (!count_quotes(&s[i], c))
				return (0);
			else
				while (s[++i] && s[i] != c[0])
					i++;
		}
		else if ((s[i] == '<' && !count_metachar(&s[i], "<", 2)) || \
				(s[i] == '>' && !count_metachar(&s[i], ">", 2)) || \
				(s[i] == '|' && !count_metachar(&s[i], "|", 1)))
				return (0);
	}
	return (1);
}

/*
int	main(int ac, char **av)
{
	(void)ac;
	char	*line;
	line = ft_strdup(av[1]);
	syntax_error_check(line);
	printf("exit_status = %d\n", exit_status);
	return (exit_status);
}
*/
