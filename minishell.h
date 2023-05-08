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
//# include "libft/includes/libft.h"
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
/*
# define 1	WORD
# define 2	PIPELINE
# define 3	LESS
# define 4	GREAT
# define 5	DLESS
# define 6	DGREAT
*/
extern int	exit_status;

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
void	free_env(t_env **head);

/* PARSING - SYNTAX ERROR CHECK */
t_token	*parsing(char *line);
int		syntax_error_check(char *s);
int		count_metachar(char *s, char c, int num);
int		count_quotes(char *s, char c);
void	print_syntax_error_char(char c);
void	print_syntax_error_dchar(char c);
void	print_syntax_error_str(char *s);

/* TOKEN EXTRACTION */
int		character_extraction(char *line, int ind);
int		token_extraction(char *line, int ind);
t_token	*get_tokens(char *line);

/* MALLOC ERROR PRINT MESSAGE */ 
void	malloc_error_print_message(char *s);

/* TOKEN EXTRACTION - TOKEN LINKED LIST */
t_token	*new_token(char *line, int start, int len);
int		token_linked_list(t_token **head, char *line, int start, int len);
int		link_token(t_token **head, t_token *new);
void	free_token(t_token **head);

/* IS SOMETHING */ 
int		is_dollar(char c);
int		is_pipeline(char c);
int		is_chevron(char c);
int		is_operator(char c);
int		is_newline(char c);
int		is_blank(char c);
int		is_metacharacter(char c);
int		is_delimiter(char c);
int		is_word(char c);
int		is_double_quote(char c);
int		is_simple_quote(char c);
int		is_quote(char c);

	// NOT OK
int		sig_handler(void);

// prototypes
void	handler_ctr_c(int code);

//int	parsing_av(char *str);
char	**ft_splitpath(char *s, char c);

void	*free_tab(void **a_free);
int		free_all(int ret);

// Prototype de readline
void  rl_replace_line(const char *test, int clear_undo);


#endif
