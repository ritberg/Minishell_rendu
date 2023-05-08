/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/08 13:21:56 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//extern int	exit_status = 0;

/*
   if quotes are not closed, call the print_error function
   to print the error message on the STDERR and set exit_status to 258.
   Then return 0 and exit the program
*/
int	count_quotes(char *s, char c)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
	{
		print_syntax_error_char(c);
		return (0);
	}
	return (1);
}

/*
   We check if there are too many characters and return 0 if yes
   We ignore blanks
   if we see more metacharacters or operators than needed
       (for ex., more than |, < or >>), we print error and return an exit status

*/
int	count_metachar(char *s, char c, int num)
{
	int	i;

	i = 0;
	i++;
	while (s[i] && s[i] == c)
		i++;
	if (i > num)
	{
		if (is_quote(c))
			print_syntax_error_dchar(c);
		else if (is_pipeline(c))
			print_syntax_error_char(c);
		return (0);
	}
	while (s[i] && is_blank(s[i]))
		i++;
	if (is_operator(s[i]))
	{
		c = s[i];
		if (is_chevron(c) && is_chevron(s[i + 1]))
				print_syntax_error_dchar(c);
		else
			print_syntax_error_char(c);
		return (0);
	}
	else if (s[i] == '\0')
		print_syntax_error_str("newline");
	return (1);
}

/*
   Goal - print an error message and return an exit status

   inside the while loop:
   - if there are quotes that are not closed, return 0,
      else if there are more metacharcaters or operators than needed, return 0
   - if we have more chevrons and pipes than |, >, >>, <, <<, return 0
*/
int	syntax_error_check(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i++])
	{
		if (is_quote(s[i]))
		{
			if (!count_quotes(&s[i], s[i]))
				return (0);
			else
			{
				c = s[i];
				i++;
				while (s[i] && s[i] != c) //?
					i++;
			}
		}
		else if ((s[i] == '<' && !count_metachar(&s[i], '<', 2)) || \
				(s[i] == '>' && !count_metachar(&s[i], '>', 2)) || \
				(s[i] == '|' && !count_metachar(&s[i], '|', 1)))
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
