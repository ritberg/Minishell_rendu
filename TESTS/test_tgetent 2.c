#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int main() {
    char term_buffer[2048]; // Tampon pour stocker les informations du terminal
    char *term_type = getenv("TERM"); // Récupère la valeur de la variable d'environnement TERM

    if (term_type == NULL) {
        fprintf(stderr, "La variable d'environnement TERM n'est pas définie.\n");
        return 1;
    }

    // Initialisation de la structure terminfo
    if (tgetent(term_buffer, term_type) != 1) {
        fprintf(stderr, "Impossible d'obtenir les informations du terminal.\n");
        return 1;
    }

    // Récupération d'une capacité spécifique
    char *cursor_motion = tgetstr("cm", NULL);
    if (cursor_motion == NULL) {
        fprintf(stderr, "La capacité cm (déplacement du curseur) n'est pas prise en charge par ce terminal.\n");
        return 1;
    }

    printf("Les informations du terminal %s ont été récupérées avec succès.\n", term_type);
    printf("La capacité cm (déplacement du curseur) est : %s\n", cursor_motion);

    return 0;
}

