#include "incognito.h"
#include <stdio.h>

#include <stdio.h>

void show_tab(int tplateau, const Jeu *jeu) {
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
            if (jeu->plateau[i][j].couleur == NOIR) {
                printf("n");
            } else if (jeu->plateau[i][j].couleur == BLANC) {
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
    int result;

    result = scanf("%d", &a.x);
    if (result != 1) {
        a.x = -1;
        return a;
    }

    result = scanf("%d", &a.y);
    if (result != 1) {
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