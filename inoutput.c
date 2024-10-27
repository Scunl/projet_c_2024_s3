#include "incognito.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void show_tab_triche(int tplateau, Jeu *game) {
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

void show_tab(int tplateau, Jeu *game) {
    printf("   ");
    for (int j = 0; j < tplateau; j++) {
        printf("%c|%d  ", 'a' + j, j);
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
                if (game->plateau[i][j].type != CHATEAU)
                    printf("n");
                else
                    printf(" ");
            } else if (game->plateau[i][j].couleur == BLANC) {
                if (game->plateau[i][j].type != CHATEAU)
                    printf("b");
                else
                    printf(" ");
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

void convert(Case pos, char *notation) {
    notation[0] = 'a' + pos.y;
    notation[1] = '1' + (TAILLE - pos.x - 1);
    notation[2] = '\0';
}

void sauvegarde_deroule(FILE *fichier, Couleur tour_initial, Mouvement *coups,
                        int nb_coups, Case *espions) {
    char notation[3];
    if (nb_coups == 0) {
        fprintf(fichier, "Tour initial : %s",
                (tour_initial == BLANC) ? "Blanc\n" : "Noir\n");
    }

    // Écriture de la position initiale des espions
    convert(espions[1], notation); // Espion blanc
    fprintf(fichier, "B %s\n", notation);

    convert(espions[0], notation); // Espion noir
    fprintf(fichier, "N %s\n", notation);

    // Écriture des mouvements
    for (int i = 0; i < nb_coups; i++) {
        char type_action = (coups[i].depart.x == coups[i].arrivee.x &&
                            coups[i].depart.y == coups[i].arrivee.y)
                               ? 'I'
                               : 'D';

        convert(coups[i].depart, notation); // Notation de départ
        fprintf(fichier, "%c %s->", type_action, notation);

        convert(coups[i].arrivee, notation); // Notation d'arrivée
        fprintf(fichier, "%s\n", notation);
    }
}
