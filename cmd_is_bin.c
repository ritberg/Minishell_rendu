#include "minishell.h"

/*
void	free_tab(char **table)
{
	int	i;

	i = 0;
	while (table && table[i])
		free(table[i++]);
	free(table);
}

int find_path_in_env(char *all_paths, char **env_table)
{
	int	i;

	i = 0;
	while (env_table[i] && ft_strncmp("PATH=", env_table[i], 5) == 0)
		i++;
    if (!env_table[i])
        return (1);
    all_paths = ft_strdup((env_table[i] + 5));
	if (!all_paths)
    {
        malloc_error_print_message("ft_strdup failed");
		return (0);
    }
	return (1);
}


int	split_paths(char *all_paths, char *cmd)
{
	char	*tmp1;
    char   **splitted_path;
	int		j;
    
    if (!all_paths)
        return (1);
    splitted_path = ft_split(all_paths, ':');
	if (!splitted_path)
    {
        malloc_error_print_message("ft_split failed");
		return (0);
    }
	j = 0;
	while (splitted_path[j])
	{
		tmp = ft_strjoin(splitted_path[j], "/");
		if(!tmp)
        {
            malloc_error_print_message("ft_strjoin failed");
			free_tab2d(splitted_path);
            return (0);
        }
		free(splitted_path[j]);
        splitted_path[j] = ft_strjoin(tmp, cmd);
        if (!splitted_path[j])
        {
            //free comme il faut
            malloc_error_print_message("ft_strjoin failed");
            return(0);
        }
        free(tmp);
        tmp = NULL;
		j++;
	}
	return (1);
}


int	find_cmd_in_path(t_cmd *cmd, char **splitted_path)
{
	int	j;
    int res;

	j = 0;
    res = 0;
	while (splitted_path[j] && access(bin->cmd, F_OK & X_OK) != 0)
		j++;
    if (!splitted_path[j])
        return (1);
    if (res == 0)
    {
        cmd->path = ft_strdup(splitted_path[j]);
        if (!cmd->path)
        {
            malloc_error_print_message("ft_strdup failed");
            free_tab2d(splitted_path);
            return (0);
        }
    }
	return (1);
}

int	find_cmd_path(t_cmd *cmd)
{
    char **splitted_path;
    char *all_paths;
    
    splitted_path = NULL;
    all_paths = NULL;
    if (!find_path_in_env(all_paths, g_shell->save_env))
        return (0);
    splitted_path = split_paths(all_paths, cmd->cmd[0]))
    free(all_paths);
    if (!splitted_path)
		return (0);
	if (!find_cmd_in_path(splitted_paths, cmd))
		return (0);
    free_tab2d(splitted_path);
	return (1);
}*/
