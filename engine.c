#include "incognito.h"
#include <stdlib.h>
#include <time.h>

int nb_pion(int tplateau) {
    if (tplateau <= 8)
        return ((tplateau - 1) * (tplateau - 2) / 2) - 1;
    return -1;
}

void init_plateau(int tplateau, Jeu *jeu) {
    int tmp = 2;
    int tmp2 = -2;
    int spyn = 0, spyb = 0;
    srand(time(NULL));

    for (int i = 0; i < tplateau; i++) {
        for (int j = 0; j < tplateau; j++) {
            jeu->plateau[i][j].couleur = 0;
            jeu->plateau[i][j].type = 0;
        }
    }

    for (int i = 0; i < tplateau; i++) {
        for (int j = 0; j < tplateau; j++) {
            if (i < tplateau - 2 && j >= tmp) {
                if (i != 0 || j != tplateau - 1) {
                    jeu->plateau[i][j].couleur = NOIR;
                    jeu->plateau[i][j].type = CHEVALIER;
                    if (spyn < 1) {
                        spyn += rand() % 2;
                        if (spyn >= 1)
                            jeu->plateau[i][j].type = ESPION;
                    }
                } else {
                    jeu->plateau[i][j].couleur = 8;
                }
            }
            if (i >= 2 && j <= tmp2) {
                if (i != tplateau - 1 || j != 0) {
                    jeu->plateau[i][j].couleur = BLANC;
                    jeu->plateau[i][j].type = CHEVALIER;
                    if (spyn < 1) {
                        spyn += rand() % 2;
                        if (spyb >= 1)
                            jeu->plateau[i][j].type = ESPION;
                    }
                } else
                    jeu->plateau[i][j].couleur = 9;
            }
        }
        tmp++;
        tmp2++;
    }
}

void shift(Jeu *jeu, Mouvement choix) {
    Couleur tmp;
    tmp = jeu->plateau[choix.depart.x][choix.depart.y].couleur;

    jeu->plateau[choix.depart.x][choix.depart.y].couleur =
        jeu->plateau[choix.arrivee.x][choix.arrivee.y].couleur;

    jeu->plateau[choix.arrivee.x][choix.arrivee.y].couleur = tmp;
}

// Pion select_spy(int nb_pion, Jeu *jeu) {
//     int nbgen1 = 0, nbgen2 = 0;
//     srand(time(NULL));
//     nbgen1 = rand() % nb_pion;
//     nbgen2 = rand() % nb_pion;
// }

void examine();
