#include "incognito.h"
#include <stdio.h>

void show_tab(int tplateau, const Jeu *jeu) {
    for (int i = 0; i < tplateau; i++) {
        for (int j = 0; j < tplateau; j++) {
            printf("%d ", jeu->plateau[i][j].couleur);
        }
        printf("\n");
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