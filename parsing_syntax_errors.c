/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/07 15:16:35 by mmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//extern int	exit_status = 0;

/*
   We print error message, which character has a problem and
   return exit status for syntax errors (258)
*/
void	print_error_syntax(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'\n", 2);
	exit_status = 258;
}

/*
   if quotes are not closed, print error and return 0
*/
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

/*
   We check if we have too many characters and return 0 if yes
   We ignore blanks
   if (is_metacharacter(s[i]) || is_operator......

*/
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

/*
   Goal - print an error message and return an exit status

   inside the while loop:
   - if there are quotes that are not closed, return 0, else ....
   - if we have more chevrons and pipes than |, >, >>, <, <<, return 0
*/
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
				while (s[++i] && s[i] != c[0]) //?
					i++;
		}
		else if ((s[i] == '<' && !count_metachar(&s[i], "<", 2)) || \
				(s[i] == '>' && !count_metachar(&s[i], ">", 2)) || \
				(s[i] == '|' && !count_metachar(&s[i], "|", 1)))
				return (0);
	}
	return (1);
}

// Main to test syntax errors
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
