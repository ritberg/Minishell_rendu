# include "minishell.h"

int	is_operator(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_variable(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_metacharacter(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (!(is_blank(c)) && !(is_metacharacter(c)) && !(is_operator(c)) && \
		   	!(is_variable(c)))
		return (1);
	return (0);
}

int	is_delimiter(char c)
{
	if (is_blank(c) || is_metacharacter(c) || is_operator(c) || is_variable(c))
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

int	is_simple_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}
