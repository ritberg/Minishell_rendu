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

int	path_index(t_bin *bin, char **table)
{
	int	i;

	i = 0;
	bin->path = NULL;
	while (table[i] != 0)
	{
		if (ft_strncmp("PATH=", table[i], 5) == 0)
		{
			bin->path = table[i] + 5;
			break ;
		}
		i++;
	}
	if (!bin->path)
		return (0);
	return (1);
}


int	split_path(t_bin *bin)
{
	char	*tmp;
	int		j;

	bin->splitted_path = ft_split(bin->path, ':');
	if (!bin->splitted_path)
		return (0);
	j = 0;
	while (bin->splitted_path[j])
	{
		tmp = ft_strjoin(bin->splitted_path[j], "/");
		if (!bin->splitted_path)
			return (0);
		free(bin->splitted_path[j]);
		bin->splitted_path[j] = tmp;
		j++;
	}
	return (1);
}


int	find_cmd_in_path(t_bin *bin, char *token)
{
	int	j;

	j = 0;
	while (bin->splitted_path[j])
	{
		bin->cmd = ft_strjoin(bin->splitted_path[j], token);
		if (!bin->cmd)
			return (0);
		bin->ok = access(bin->cmd, F_OK & X_OK);
		if (bin->ok == 0)
			break ;
		//free(bin->cmd);
		j++;
	}
	free_tab(bin->splitted_path);
	if (bin->ok == -1)
		return (0);
	return (1);
}

int	cmd_is_bin(t_cmd **cmd)
{
	if (!path_index(cmd, g_shell->save_env))
		return (-1);
	if (!split_path(cmd))
		return (-1);
	if (!find_cmd_in_path(cmd))
		return (-1);
	return (1);
}*/
