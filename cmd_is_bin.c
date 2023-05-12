#include "minishell.h"

int	path_line_index(t_env *env)
{
	int	i;

	i = 0;
	while (env->var_name != NULL)
	{
		if (ft_strncmp("PATH=", env->var_name, 5) == 0)
			break ;
		i++;
		env->var_name = env->next;
	}
	return (i);
}

t_env	*path_value(t_env *env, int nb)
{
	int	i;

	i = 0;
	while (env->var_value && i != nb)
	{
		env->var_value = env->next;
		i++;
	}
	return (env->var_value);
}

char	**split_var_value(char *value)
{
	char	**paths;
	char	*temp_path;
	int		j;

	paths = ft_split(value, ':');
	if (!paths)
		return (0);
	j = 0;
	while (paths[j])
	{
		temp_path = ft_strjoin(paths[j], "/");
		if (!temp_paths)
			return (0);
		free(paths[j]);
		paths[j] = temp_path;
		j++;
	}
	return (paths);
}

int	find_cmd_bin(char **paths, t_env *env, t_token *token)
{
	int	j;
	int	ok;
	char	*cmd;
	
	j = 0;
	while (paths[j])
	{
		cmd = ft_strjoin(paths[j], token->content);
		if (!cmd)
			return (0);
		ok = access(cmd, F_OK & X_OK);
		if (ok == 0)
			break ;
		free(cmd);
		j++;
	}
	if (ok == -1)
		return (0);
	return (1);
}

int	bin_access(t_token *token)
{
	int	nb;
	char	*value;
	char	**bins;

	if (token->id == WORD)
	{
		nb = path_line_index(g_shell->env);
		value = path_value(g_shell->env, nb);
		bins = split_var_value(value);
		if (!find_cmd_bin(bins, g_shell->env, g_shell->token)) //??
			return (0); //??? is bin??
	}
	return (1);
}
