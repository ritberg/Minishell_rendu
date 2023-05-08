/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token_extraction.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:00:21 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/08 18:25:54 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TOKENIZATION AVANT EXPANSION ET QUOTE REMOVING

int	exit_status = 0;

/*
   calculate len of a 'word' containing characters
   if we have two chevrons >> or <<, return 2
   else return 1
*/
int	character_extraction(char *line, int ind)
{
	if ((line[ind] == '>' && line[ind + 1] == '>') || \
		(line[ind] == '<' && line[ind + 1] == '<'))
		return (2);
	return (1);
}

/*
   is it correct ??
*/
int	word_extraction(char *line, int ind)
{
	int	start;
	char	c;

	start = ind;
	while (is_word(line[ind]) && line[ind])
	{
		if (is_quote(line[ind]))
		{
			c = line[ind];
			ind++;
			while (line[ind] && line[ind] != c)
				ind++;
		}
		ind++;
	}
	return (ind - start);
}

/*
   Goal - extract words from char *line and return them as tokens

   - check syntax errors
   - inside the while loop while(line[i])
   		- ignore blanks
		- if there are quotes, calculate the word len with 
			the function quotes_word_extraction (see above)
		- if there is a character or $, calculate the word len with 
			the function word_extraction (see above)
		- if there is a metacharacter or operator, calculate the 'word' len
			with the function character_extraction (see above)
		- create a head with the function new_token (if there is no head yet)
		- if there is a head already at this iteration, create a
			linked list of tokens with thi function token_linked_list
*/
/*
typedef	struct s_point
{
	int	start;
	int	size;
}

t_point	*get_token_size(char *line, )
{
	t_point	*point;

}
*/
t_token	*get_tokens(char *line) // A RACCOURCIR
{
	int			i;
	int			len;
	int			flag;
	t_token		*head;

	i = 0;
	len = 0;
	flag = 0;
	head = NULL;
	while (line[i])
	{
		while (is_blank(line[i]))
			i++;
		if (is_word(line[i]))
			len = word_extraction(line, i);
		else if (is_operator(line[i]))
			len = character_extraction(line, i);
		if (flag == 0)
		{
			head = new_token(line, i, len);
			if (!head)
				return (free_token(&head), NULL);
			flag = 1;
		}
		else
			if (!token_linked_list(&head, line, i, len))
				return (free_token(&head), free(line), NULL);
		i += len;
	}
	return (free(line), head);
}

/*
   Temporary main
   Goal - create a linked list of extracted words (see get_words(line))
   
   - save the first element as head
   - if there is no head, return exit_status
   - if there is a head, create a linked list 
   		with a pointer ptr using t_token structure
   - free head
*/
/*
int	main(int ac, char **av)
{
	(void)ac;
	t_token	*head;
	t_token	*ptr;
	char	*line;
	
	line = NULL;
	head = NULL;
	line = ft_strdup(av[1]);
	head = get_words(line);
	if (!head)
	{
		printf(" exit from main\n");  //A SUPPRIMER
		return (exit_status);
	}
	ptr = head;
	while (ptr)
	{
		printf("from main: %s\n", ptr->content); // A SUPPRIMER
		ptr = ptr->next;
	}
	free_token(&head);
	return (exit_status);
}


// Old main to do tests inside this file


int	main(int ac, char **av)
{
	*t_token	*head;
	t_token	*ptr;
	int		i;
	int		j;
	char	**line;

	i = 0;
	j = 1;
	line = malloc(sizeof(char *) * ac);
	while (av[j])
	{
		line[i] = ft_strdup(av[j]);
		i++;
		j++;
	}
	line[i] = NULL;
	head = NULL;
	head = new_token(line[0], 0, ft_strlen(line[0]));
	if (!head)
	{
		printf("malloc: %s\n", strerror(errno));
		return (1);
	}
	i = 1;
	while (line[i])
	{
		token_linked_list(&head, line[i], 0, ft_strlen(line[i]));
		i++;
	}
	i = 0;
	ptr = head;
	while (ptr)
	{
		printf("%s\n", ptr->content);
		ptr = ptr->next;
		i++;
	}
	free_token(&head);
	return (exit_status);
}
*/
