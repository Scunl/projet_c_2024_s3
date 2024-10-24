#include "incognito.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nb_pion(int tplateau) {
    if (tplateau <= 8)
        return ((tplateau - 1) * (tplateau - 2) / 2) - 1;
    return -1;
}

void init_plateau(int tplateau, Jeu *game) {
    int tmp = 2;
    int tmp2 = -2;
    int spyn = 0, spyb = 0;

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
                            printf("spyn : %d %d\n", i, j);
                        }
                    }
                } else {
                    game->plateau[i][j].couleur = 8;
                }
            }
            if (i >= 2 && j <= tmp2) {
                if (i != tplateau - 1 || j != 0) {
                    game->plateau[i][j].couleur = BLANC;
                    game->plateau[i][j].type = CHEVALIER;
                    if (spyb < 1) {
                        spyb += rand() % 2;
                        if (spyb >= 1) {
                            printf("spyb : %d %d\n", i, j);
                            game->plateau[i][j].type = ESPION;
                        }
                    }
                } else
                    game->plateau[i][j].couleur = 9;
            }
        }
        tmp++;
        tmp2++;
    }
}

void shift(Jeu *game, Mouvement choix) {
    Couleur tmp;
    tmp = game->plateau[choix.depart.x][choix.depart.y].couleur;

    game->plateau[choix.depart.x][choix.depart.y].couleur =
        game->plateau[choix.arrivee.x][choix.arrivee.y].couleur;

    game->plateau[choix.arrivee.x][choix.arrivee.y].couleur = tmp;
}


int examine(Jeu *game, Mouvement pion) {
    if (game->plateau[pion.arrivee.x][pion.arrivee.y].type == ESPION)
        return 1;
    return 0;
}
