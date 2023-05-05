#ifndef CLASS_H
# define CLASS_H

# include "minishell.h"

typedef struct s_line
{
	int				ind;
	char			*line;
	struct s_line	*next;
	struct s_line	*prev;

}	t_line;

typedef struct s_var
{
	int				ind;
	int				id;
	char			**envp;
	char			*key;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;

}	t_var;

typedef struct s_token
{
	void			*type;
	int				id;
	struct s_line	*next;
	struct s_line	*prev;

}	t_token;

typedef struct s_arg
{
	char			*content;
	int				id;
	int				ind;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_cmd
{
	int		id;
	char	*content;
	char	*path_envp;
	char	**mypaths;
	char	**args;
	t_arg	*arg;

}	t_cmd;

typedef struct s_file
{
	char	*name;
	int		fd;

}	t_file;

typedef struct s_redir
{
	char	*content;
	char	*delimiter;
	int		fd_in;
	int		fd_out;

}	t_redir;

typedef struct s_pipe
{
	char	*content;
	char	pipe_c;
	int		fd_in;
	int		fd_out;

}	t_pipe;


#endif
