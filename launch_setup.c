
#include "minishell.h"

/*
   Function that manages ctrl c, ctrl d and ctrl \
   
   ! Il faut voir comment retourner le bon exit status
   suivant quelle touche a ete appuye
 */

int	sig_handler(void)
{
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN); //ctrl D dsn't send signals; ctrl \ sends SEGQUIT
	return (0);
}
