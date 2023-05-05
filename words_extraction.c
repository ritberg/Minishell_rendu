#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

int	character_extraction(char *line, int ind)
{
	if ((line[ind] == '>' && line[ind + 1] == '>') || \
			(line[ind] == '<' && line[ind + 1] == '<'))
		return (2);
	return (1);
}


int	word_extraction(char *line, int ind)
{
	int	start;
	char	c;

	start = ind;
	while (line[ind])
	{
		if ((is_simple_quote(line[ind]) && ft_strchr(line + ind + 1, '\'')) \
				|| (is_double_quote(line[ind]) && ft_strchr(line + ind + 1, '\"')))
		{
			c = line[ind++];
			while (line[ind] != c)
			{
				ind++;
			}
			ind++;
		//	return (ind - start);
		}	
		if (is_delimiter(line[ind]) == 1)
			return (ind - start);
		ind++;
	}
	return (ind - start);
}

int	quotes_word_extraction(char *line, int ind, char c)
{
	int	start;

	start = ind;
	ind++;
	while (line[ind] && line[ind] != c)
		ind++;
	return (ind - start);
}

char	*get_words(char *line)
{
	//t_list	line;
	int	i;
	int	len;
	char	*content;

	i = 0;
	len = 0;
//	line = malloc(sizeof(t_list));

	while (line[i])
	{
		if (is_blank(line[i]))
			i++;
		if (is_word(line[i]) || is_variable(line[i]))
			len = word_extraction(line, i); //il faut enlever des quotes ""
		else if (is_metacharacter(line[i]) || is_operator(line[i]))
			len = character_extraction(line, i);
		else if (line[i] == '\'' || line[i] == '\"')
		{
			if (ft_strchr((line + i + 1), line[i]))
				len = quotes_word_extraction((line + i + 1), i, line[i]);
			else
				printf("Error: number of quotes is not even\n");
		}
		content = ft_substr(line, i, len);
		printf("%s\n", content);
		i += len;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	char	*line = ft_strdup(av[1]);
	
	get_words(line);
	return (0);
}
