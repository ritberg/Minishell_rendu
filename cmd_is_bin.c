#include "minishell.h"

/*

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

void free_helper(char *s1, char *s2, char *s3, char **s4)
{
    if (s1)
        free(s1);
    if (s2)
        free (s2);
    if (s3)
        free (s3);
    free_tab2d(s4);
}

int	split_paths(char *all_paths, char *cmd)
{
	char	*tmp1;
    char *tmp2;
    char   **splitted_path;
	int		j;
    
    
    tmp1 = NULL;
    tmp2 = NULL;
    splitted_path = NULL;
    if (!all_paths)
        return (1);
    tmp2 = ft_strjoin("/", cmd->cmd0);
    if (!tmp2)
    {
        free_helper(tmp1, tmp2, all_paths, splitted_path);
        malloc_error_print_message("ft_strjoin failed");
        return (0);
    }
    splitted_path = ft_split(all_paths, ':');
	if (!splitted_path)
    {
        free_helper(tmp1, tmp2, all_paths, splitted_path);
        malloc_error_print_message("ft_split failed");
		return (0);
    }
	j = 0;
	while (splitted_path[j])
	{
		tmp1 = ft_strjoin(splitted_path[j], tmp2);
		if(!tmp1)
        {
            free_helper(tmp1, tmp2, all_paths, splitted_path);
            malloc_error_print_message("ft_strjoin failed");
            return (0);
        }
        if (access(bin->cmd, F_OK & X_OK) == 0)
        {
            cmd->path = ft_strdup(tmp1);
            free_helper(tmp1, tmp2, all_paths, splitted_path);
            if (!cmd->path)
            {
                malloc_error_print_message("ft_strdup failed");
                return (0);
            }
            return(1);
        }
        free(tmp);
        tmp = NULL;
		j++;
	}
    free_helper(tmp1, tmp2, all_paths, splitted_path);
    cmd->path = ft_strjoin("/bin/", cmd->cmd[0]);
    if (!cmd->path)
    {
        malloc_error_print_message("ft_strdup failed");
        return (0);
    }
	return (1);
}

int	find_cmd_path(t_cmd *cmd)
{
    char *all_paths;
    
    all_paths = NULL;
    if (!find_path_in_env(all_paths, g_shell->save_env))
        return (0);
    if (!split_paths(all_paths, cmd->cmd[0]))
		return (0);
	return (1);
}*/
