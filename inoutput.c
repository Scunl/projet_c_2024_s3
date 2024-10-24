#include "incognito.h"
#include <stdio.h>
#include <stdio.h>

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
                printf("n");
            } else if (game->plateau[i][j].couleur == BLANC) {
                printf("b");
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

    scanf("%d", &a.x);
    if (a.x < 0 || a.x > TAILLE - 1) {
        a.x = -1;
        return a;
    }

    scanf("%d", &a.y);
    if (a.y < 0 || a.y > TAILLE - 1) {
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
