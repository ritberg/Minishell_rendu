#include "minishell.h"

void	exec_bin(t_token *token, t_bin *bin)
{
	int	status;

	bin->child = fork();
	if (bin->child < 0)
		return (perror("Fork: "));
	if (bin->child == 0)
		execve(bin->cmd, &token->content, g_shell->save_env);
	else
		waitpid(bin->child, &status, 0);
}

void	check_then_execute(t_token *token)
{
	t_bin	*bin;

	bin = malloc(sizeof(t_bin));
	g_shell->save_env = copy_env_tab(g_shell->env);
	if (token->id == WORD)
	{
		if (cmd_is_bin(token, bin))
			exec_bin(token, bin);
	//	if (cmd_is_builtin(token))
	//		exec_builtin(token);
	//	if (cmd_is_fd(token))
	//		open_fd(token);
	}
}
