/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_ctr_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:12:07 by mdanchev          #+#    #+#             */
/*   Updated: 2023/05/09 13:15:42 by mdanchev         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	handler_ctr_c(int code)
{

	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//exit(1);
}
/*
    rl_replace_line("", 0);
    Cette ligne remplace la ligne de texte dans la bibliothèque
	Readline de la mémoire tampon de ligne avec une chaîne vide
	et d'une longueur de 0. 

    rl_on_new_line();
    Cette ligne déplace le curseur sur une nouvelle ligne dans la bibliothèque
	Readline de la mémoire tampon de ligne. 

    rl_redisplay();
    Cette ligne affiche à nouveau la ligne de texte dans la bibliothèque
	Readline de la mémoire tampon de ligne, qui est maintenant une chaîne vide.

Dans l'ensemble, cette fonction est un gestionnaire de signal
pour le signal d'interruption (SIGINT) qui est déclenché lorsque l'utilisateur
appuie sur Ctrl+C. Lorsque le signal est pris, il efface la ligne de texte
dans le Readline tampon et imprime un caractère de saut de ligne à la console
*/
