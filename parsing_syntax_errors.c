/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_errors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:31 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 13:21:14 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

int	check_multiple_operators_error(int i, int num, char c)
{
	if (i > num)
	{
		if (is_chevron(c))
			print_syntax_error_dchar(c);
		else if (is_pipeline(c))
			print_syntax_error_char(c);
		return (0);
	}
	return (1);
}

void	operator_before_newline_error(char c)
{
	if (is_pipeline(c))
		print_syntax_error_char(c);
	else
		print_syntax_error_str("newline");
}

//DE MARIYA:
//POUR RACCOURCIR LA FONCTION count_metachar
//J'AI CREE DEUX FONCTIONS SUPPLEMENTAIRES CI-DESSUS
//operator_before_newline_error ET check_multiple_operators_error
int	count_metachar(char *s, char c, int num)
{
	int	i;

	i = 1;
	while (s[i] && s[i] == c)
		i++;
	if (!check_multiple_operators_error(i, num, c))
		return (0);
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
	{
		operator_before_newline_error(c);
		return (0);
	}
	pipeline(check);
	return (1);
}

/*
 * syntax_error_check function:
 * GOAL - before token splitting, check for syntax error
 * 		  print an error message and exit status the status to 258
 *
 * Inside the while loop:
 *	- if it find a quote -> call count_quotes function
 *	  
 *	  count_quotes function:
 *	  	- verifies if quotes are closed or not.
 *	  	- all metacharcter loose their special meaning inside quotes.
 *	  	  If a metacharcter is found inside quotes, 
 *	  	  it is considered as a regular character.
 *	  	- if quotes is unclosed, the function prints error message 
 *	  	  and sets the exit status to 258
 *  
 *  - if it finds a metacharcater (<, >, |) -> call the count_metachar function
 * 	  
 * 	  count_metachar function:
 * 	  	- verifies whether there are too many metacharacters (ex. >>>, |||)
 * 	  	- verifies if there are two operators in a row (ex. > <, | |, > |)
 * 	  	- verfies if there is a newline after a metacharacter (ex. >\n, |\n)
 * 	  	- for pipeline verifies if there are caracters from both sides of the pipe
 * 	  	  (|test -> error, test| -> error, test1|test2 -> ok)
 * 	  If one of these conditions is true, the function prints error message
 * 	  and sets the exit status to 258
*/

int	syntax_error_check(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
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
		i++;
	}
	return (1);
}
