#ifndef __INCOGNITO_H__
#define __INCOGNITO_H__

#include <stdio.h>

#define TAILLE 5
#define MAX_COUPS 100

typedef enum _couleur { VIDE, BLANC, NOIR } Couleur;
typedef enum _type { CHEVALIER, ESPION, CHATEAU } Type;

typedef struct _pion {
    Type type;
    Couleur couleur;
} Pion;

typedef struct _vecteur {
    int x, y;
} Case, Direction;

typedef struct _jeu {
    Pion plateau[TAILLE][TAILLE];
    Couleur joueur;
} Jeu;

typedef struct _mouvement {
    Case depart;
    Case arrivee;
} Mouvement;

int nb_pion(int tplateau);
Case *init_plateau(int tplateau, Jeu *game);
void show_tab(int tplateau, Jeu *game, int triche);
Case parse(void);
void shift(Jeu *game, Mouvement choix);
int examine(Jeu *game, Mouvement pion);
void gagnant(Couleur color);
Couleur gen_tour();
void save_game(FILE *fichier, Mouvement coup, Couleur tour, int nb_coups);
void sauvegarde_deroule(FILE *fichier, Mouvement pion, int nbcoups,
                        Couleur tour, Case *espion);
void convert(Case pos, char *notation);
void convert_inverse(char *notation, Case *position);

#endif
