
#include "minishell.h"
#include "class.h"

/*
 * Il faut voir comment retourner lebon exit status
 * suivant quelle touche a ete appuiye
 */

int	sig_handler(void)
{
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN); //ctrl D dsn't send signals; ctrl \ sends SEGQUIT
	return (0);
}
/*
Dans l'ensemble, cette fonction définit les gestionnaires de signaux
pour l'interrompre et arrêter de signaux, attribue la valeur d'un paramètre
à une variable globale, initialise une autre variable globale, et appelle
une fonction.
*/ 
