#include "incognito.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    Jeu jeu;
    Mouvement pion;
    init_plateau(TAILLE, &jeu);
    show_tab(TAILLE, &jeu);
    Couleur tour = BLANC;
    int partie = 1;

    while (partie) {
        do {
            printf("============================\n");
            if (tour == BLANC)
                printf("C'est au tour du joueur Blanc\n");
            else
                printf(" > C'est au tour du joueur Noir\n");
            printf(
                "  >  Séléctionnez les coordonées du pion que vous souhaitez "
                "déplacer\n  > ");
            pion.depart = parse();
            if (pion.depart.x == -1 || pion.depart.y == -1) {
                while (getchar() != '\n')
                    ;
                printf("Coordonnées invalides, veuillez réessayer.\n");
                continue;
            }
        } while (((pion.depart.x >= TAILLE || pion.depart.x < 0 ||
                   pion.depart.y >= TAILLE || pion.depart.y < 0) ||
                  (jeu.plateau[pion.depart.x][pion.depart.y].couleur != tour)));

        do {
            printf("  > Séléction du pion en x : %d et y : %d\n"
                   "    >   Vers quelle case voulez-vous effectuer votre coup "
                   "?\n    > ",
                   pion.depart.x, pion.depart.y);
            pion.arrivee = parse();
            if (pion.arrivee.x == -1 || pion.arrivee.y == -1) {
                while (getchar() != '\n')
                    ;
                printf("Coordonnées invalides, veuillez réessayer.\n");
                continue;
            }
        } while (((pion.depart.x >= TAILLE || pion.depart.x < 0 ||
                   pion.depart.y >= TAILLE || pion.depart.y < 0) ||
                  (jeu.plateau[pion.depart.x][pion.depart.y].couleur != tour) ||
                  (abs(pion.depart.x - pion.arrivee.x) > 1) ||
                  abs(pion.depart.y - pion.arrivee.y) > 1));
                  
        if ((jeu.plateau[pion.arrivee.x][pion.arrivee.y].couleur == 0))
            shift(&jeu, pion);
        // examine();
        show_tab(TAILLE, &jeu);
        tour = (tour == NOIR) ? BLANC : NOIR;
    }
    return 0;
}
