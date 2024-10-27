#include "incognito.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction d'affichage du tableau : On peut choisir de visualiser les espions
// ou non.
void show_tab(int tplateau, Jeu *game, int triche) {
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
                    if (triche)
                        printf(game->plateau[i][j].type == CHEVALIER ? "n"
                                                                     : "N");
                    else
                        printf("n");

                else
                    printf(" ");
            } else if (game->plateau[i][j].couleur == BLANC) {
                if (game->plateau[i][j].type != CHATEAU)
                    if (triche)
                        printf(game->plateau[i][j].type == CHEVALIER ? "b"
                                                                     : "B");
                    else
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

// fonction permettant de prendre 2 inputs valide de l'utilisateur
// et de retourner un type Case
// La fonction met les valeurs de x et y dans la structure Case à -1
// si l'utilisateur met un caractère et -2 si l'utilisateur envoie un 'q'
Case parse(void) {
    Case depart;
    char input[10];

    if (scanf("%9s", input) == 1 && input[0] == 'q') {
        depart.x = -2;
        return depart;
    }
    depart.x = atoi(input);
    if (depart.x < 0 || depart.x >= TAILLE) {
        depart.x = -1;
        return depart;
    }

    if (scanf("%9s", input) == 1 && input[0] == 'q') {
        depart.x = -2;
        return depart;
    }
    depart.y = atoi(input);
    if (depart.y < 0 || depart.y >= TAILLE) {
        depart.y = -1;
    }

    return depart;
}

// Fonction d'affichage du gagnant
void gagnant(Couleur color) {
    if (color == BLANC)
        printf("Les blancs ont gagné la partie !\n");
    else
        printf("Les noirs ont gagné la partie !\n");
}

// Cette fonction convert permet de convertir des nombres (1,2,3..) en
// (a,b,c...)
void convert(Case pos, char *notation) {
    notation[0] = 'a' + (pos.y);
    notation[1] = '1' + (TAILLE - 1 - pos.x);
    notation[2] = '\0';
}

// Cette fonction doit convertir la notation (comme "a1", "b2") en coordonnées
// (x, y)
void convert_inverse(char *notation, Case *position) {
    position->x = notation[1] - '1';
    position->y = notation[0] - 'A';
}

// Sauvegarde la partie dans un fichier texte
void sauvegarde_deroule(FILE *fichier, Mouvement pion, int nbcoups,
                        Couleur tour, Case *espion) {
    if (!fichier)
        return;
    if (nbcoups == 0) {
        fprintf(fichier, (tour == BLANC) ? "B\n" : "N\n");
        fprintf(fichier, "Spy : %d %d\nSpy : %d %d\n", espion[0].x, espion[0].y,
                espion[1].x, espion[1].y);
    } else if (nbcoups > 0) {
            fprintf(fichier, "%c %c%d --> %c%d\n", (tour == BLANC) ? 'B' : 'N',
                    'a' + pion.depart.y, pion.depart.x + 1,
                    'a' + pion.arrivee.y, pion.arrivee.x + 1);
    }
}
