#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"

# define RED    "\x1b[31m"
# define BLU    "\x1B[34m"
# define BLU_2 "\e[1;34m"
# define GRN    "\x1B[32m"
# define YEL    "\x1B[33m"
# define MAG    "\x1B[35m"
# define CYN    "\x1B[36m"
# define WHT    "\x1B[37m"
# define RESET  "\x1B[0m"


// OK
typedef struct s_env
{
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char				*content;
	int					id;
	struct s_token		*next;
}						t_token;

/* GETENVP */
t_env	**get_envp(char **envp);

/* PARSING - SYNTAX ERROR CHECK */
int		word_extraction(char *line, int ind);
int		syntax_error_check(char *s);
int		quotes_word_extraction(char *line, int ind, char c);
char	*get_words(char *line);

/* WORD_EXTRACTION */
int		character_extraction(char *line, int ind);

/* IS SOMETHING */ 
int		is_blank(char c);
int		is_operator(char c);
int		is_variable(char c);
int		is_metacharacter(char c);
int		is_word(char c);
int		is_delimiter(char c);
int		is_simple_quote(char c);
int		is_double_quote(char c);

	// NOT OK
int		sig_handler(void);

// prototypes
void	handler_ctr_c(int code);

//int	parsing_av(char *str);
char	**ft_splitpath(char *s, char c);

void	*free_tab(void **a_free);
int		free_all(int ret);



#endif
