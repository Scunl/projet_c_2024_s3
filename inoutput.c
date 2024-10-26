#include "incognito.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


void show_tab(int tplateau, const Jeu *game) {
    printf("   ");
    for (int j = 0; j < tplateau; j++) {
        printf("  %d ", j);
    }
    printf("\n");

    printf("   ");
    for (int i = 0; i < tplateau; i++) {
        printf("----");
    }
    printf("-\n");

    for (int i = 0; i < tplateau; i++) {
        printf(" %d ", i);

        for (int j = 0; j < tplateau; j++) {
            printf("| ");
            if (game->plateau[i][j].couleur == NOIR) {
                printf(game->plateau[i][j].type == CHEVALIER ? "n" : "N");
            } else if (game->plateau[i][j].couleur == BLANC) {
                printf(game->plateau[i][j].type == CHEVALIER ? "b" : "B");
            } else {
                printf(" ");
            }
            printf(" ");
        }
        

        printf("|\n");

        printf("   ");
        for (int j = 0; j < tplateau; j++) {
            printf("----");
        }
        printf("-\n");
    }
}

Case parse(void) {
    Case a;
    char input[10];

    if (scanf("%9s", input) == 1 && input[0] == 'q') {
        a.x = -2;
        return a;
    }
    a.x = atoi(input);
    if (a.x < 0 || a.x >= TAILLE) {
        a.x = -1;
        return a;
    }

    if (scanf("%9s", input) == 1 && input[0] == 'q') {
        a.x = -2;
        return a;
    }
    a.y = atoi(input);
    if (a.y < 0 || a.y >= TAILLE) {
        a.y = -1;
    }

    return a;
}

void gagnant(Couleur color) {
    if (color == BLANC)
        printf("Les blancs ont gagné la partie !\n");
    else
        printf("Les noirs ont gagné la partie !\n");
}

// Convertit les coordonnées en notation d'échiquier
void convertir_en_notation(Case pos, char *notation) {
    notation[0] = 'a' + pos.y;
    notation[1] = '1' + pos.x;
    notation[2] = '\0';
}

// Save le déroulé du jeu au format .inco
void sauvegarde_deroule(FILE *fichier, const Jeu *game, Couleur tour_initial, Couleur gagnant, const Mouvement *coups, int nb_coups) {
    char notation[3];

    if (fichier == NULL) {
        printf("Erreur: le fichier de sauvegarde n'est pas ouvert.\n");
        return;
    }

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (game->plateau[i][j].type == ESPION) {
                Case pos = {i, j};
                convertir_en_notation(pos, notation);

                if (game->plateau[i][j].couleur == BLANC) {
                    fprintf(fichier, "B %s\n", notation);
                } else if (game->plateau[i][j].couleur == NOIR) {
                    fprintf(fichier, "N %s\n", notation);
                }
            }
        }
    }

    fprintf(fichier, "%c\n", tour_initial == BLANC ? 'B' : 'N');

    for (int i = 0; i < nb_coups; i++) {
        convertir_en_notation(coups[i].depart, notation);
        fprintf(fichier, "%c %s -> ", game->plateau[coups[i].depart.x][coups[i].depart.y].couleur == BLANC ? 'B' : 'N', notation);

        convertir_en_notation(coups[i].arrivee, notation);
        fprintf(fichier, "%s\n", notation);
    }

    fprintf(fichier, "%c\n", gagnant == BLANC ? 'B' : 'N');
}
