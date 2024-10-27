#include "incognito.h"
#include <stdlib.h>
#include <time.h>

// calcule les pions qui peuvent etre placés sur le plateau 
// en fonction de la taille en calculant le nombre de pions en fonction de la taille 
// du plateau 

// Arguments:
// int_plateau: taille du plateau 

// valeur de retour:
// tplateau: le nombre de pions calculés 

// Exemple:
// int pions = nb_pion(8); 
// >>> 21
int nb_pion(int tplateau) {
    if (tplateau <= 8)
        return ((tplateau - 1) * (tplateau - 2) / 2) - 1;
    return -1;
}

// Crée un plateau avec des pions blancs et noirs

// Arguments:
// int tplateau: taille du plateau
// jeu *game: pointeur vers la structure jeu

// Valeur de retour:
// pointeur vers case avec les coordonnées des espions 
Case *init_plateau(int tplateau, Jeu *game) {
    int tmp = 2;
    int tmp2 = -2;
    int spyn = 0, spyb = 0;
    Case *tab = malloc(2 * sizeof(Case));
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les espions\n");
        exit(EXIT_FAILURE);
    }
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
                            tab[0].x = i;
                            tab[0].y = j;
                        }
                    }
                } else {
                    game->plateau[i][j].type = CHATEAU;
                    game->plateau[i][j].couleur = NOIR;
                }
            }
            if (i >= 2 && j <= tmp2) {
                if (i != tplateau - 1 || j != 0) {
                    game->plateau[i][j].couleur = BLANC;
                    game->plateau[i][j].type = CHEVALIER;
                    if (spyb < 1) {
                        spyb += rand() % 2;
                        if (spyb >= 1) {
                            tab[1].x = i;
                            tab[1].y = j;
                            game->plateau[i][j].type = ESPION;
                        }
                    }
                } else {
                    game->plateau[i][j].type = CHATEAU;
                    game->plateau[i][j].couleur = NOIR;
                }
            }
        }
        tmp++;
        tmp2++;
    }
    return tab;
}

// Fonction de déplacement qui prend en parametre le jeu et le mouvement de l'utilisateur
// Il n'y a pas de valeur de retour 
// Arguments:
// jeu *game: pointeur vers jeu
// mouvement choix: structure qui a les coordonnées de départ et d'arrivée
void shift(Jeu *game, Mouvement choix) {
    Couleur colormove;
    Type typemove;

    colormove = game->plateau[choix.depart.x][choix.depart.y].couleur;

    game->plateau[choix.depart.x][choix.depart.y].couleur =
        game->plateau[choix.arrivee.x][choix.arrivee.y].couleur;

    game->plateau[choix.arrivee.x][choix.arrivee.y].couleur = colormove;

    typemove = game->plateau[choix.depart.x][choix.depart.y].type;

    game->plateau[choix.depart.x][choix.depart.y].type =
        game->plateau[choix.arrivee.x][choix.arrivee.y].type;

    game->plateau[choix.arrivee.x][choix.arrivee.y].type = typemove;
}


// Vérifie si la case d'arrivée est occupée

// Arguments: 
// Mouvement pion: les coordonnées de la case d'arrivé à verifier

// valeur de retour:
// 1 si la case est occupée, 0 sinon
int examine(Jeu *game, Mouvement pion) {
    if (game->plateau[pion.arrivee.x][pion.arrivee.y].couleur != VIDE)
        return 1;
    return 0;
}

// Génère aléatoirement une couleur de tour du joueur (soit noir soit blanc)

// Valeur de retour: Couleur générée (type couleur)

// effet de bord: 
// utilise rand() pour generer un nombre aléatoire 
// basé sur l'heure actuelle, influençant les tours futurs
Couleur gen_tour() {
    srand(time(NULL));
    int nb_gen = rand() % 2;

    if (nb_gen)
        return BLANC;
    return NOIR;
}
