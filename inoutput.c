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

    scanf("%d", &a.x);
    scanf("%d", &a.y);
    
    return a;
}
