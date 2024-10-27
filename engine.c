#include "incognito.h"
#include <stdlib.h>
#include <time.h>

int nb_pion(int tplateau) {
    if (tplateau <= 8)
        return ((tplateau - 1) * (tplateau - 2) / 2) - 1;
    return -1;
}

/*Retourne les coordonnées des espions et initialise le plateau*/
Case *init_plateau(int tplateau, Jeu *game) {
    int tmp = 2;
    int tmp2 = -2;
    int spyn = 0, spyb = 0;
    Case *tab = malloc(2 * sizeof(Case));
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les espions\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    for (int i = 0; i < tplateau; i++) {
        for (int j = 0; j < tplateau; j++) {
            game->plateau[i][j].couleur = 0;
            game->plateau[i][j].type = 0;
        }
    }

    for (int i = 0; i < tplateau; i++) {
        for (int j = 0; j < tplateau; j++) {
            if (i < tplateau - 2 && j >= tmp) {
                if (i != 0 || j != tplateau - 1) {
                    game->plateau[i][j].couleur = NOIR;
                    game->plateau[i][j].type = CHEVALIER;
                    if (spyn < 1) {
                        spyn += rand() % 2;
                        if (spyn >= 1) {
                            game->plateau[i][j].type = ESPION;
                            tab[0].x = i;
                            tab[0].y = j;
                        }
                    }
                } else {
                    game->plateau[i][j].type = CHATEAU;
                    game->plateau[i][j].couleur = NOIR;
                }
            }
            if (i >= 2 && j <= tmp2) {
                if (i != tplateau - 1 || j != 0) {
                    game->plateau[i][j].couleur = BLANC;
                    game->plateau[i][j].type = CHEVALIER;
                    if (spyb < 1) {
                        spyb += rand() % 2;
                        if (spyb >= 1) {
                            tab[1].x = i;
                            tab[1].y = j;
                            game->plateau[i][j].type = ESPION;
                        }
                    }
                } else {
                    game->plateau[i][j].type = CHATEAU;
                    game->plateau[i][j].couleur = NOIR;
                }
            }
        }
        tmp++;
        tmp2++;
    }
    return tab;
}

void shift(Jeu *game, Mouvement choix) {
    Couleur colormove;
    Type typemove;

    colormove = game->plateau[choix.depart.x][choix.depart.y].couleur;

    game->plateau[choix.depart.x][choix.depart.y].couleur =
        game->plateau[choix.arrivee.x][choix.arrivee.y].couleur;

    game->plateau[choix.arrivee.x][choix.arrivee.y].couleur = colormove;

    typemove = game->plateau[choix.depart.x][choix.depart.y].type;

    game->plateau[choix.depart.x][choix.depart.y].type =
        game->plateau[choix.arrivee.x][choix.arrivee.y].type;

    game->plateau[choix.arrivee.x][choix.arrivee.y].type = typemove;
}

int examine(Jeu *game, Mouvement pion) {
    if (game->plateau[pion.arrivee.x][pion.arrivee.y].couleur != VIDE)
        return 1;
    return 0;
}

Couleur gen_tour() {
    srand(time(NULL));
    int nb_gen = rand() % 2;

    if (nb_gen)
        return BLANC;
    return NOIR;
}
