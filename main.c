#include <stdio.h>
#include <stdlib.h>
#include <incognito.h>

#define TAILLE 5 // Taille du plateau


int nb_pion(int tplateau) {
    if (tplateau <= 8)
        return ((tplateau -1)(tplateau - 2)/2.) - 1;
    else
        return -1;
}



int main(void) {
    return 0;
}