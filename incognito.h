#ifndef __INCOGNITO_H__
#define __INCOGNITO_H__

#define TAILLE 5

typedef enum _couleur { VIDE, BLANC, NOIR } Couleur;
typedef enum _type { CHEVALIER, ESPION } Type;

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
void init_plateau(int tplateau, Jeu *game);
void show_tab(int tplateau, const Jeu *game);    
Case parse(void);
void shift(Jeu *game, Mouvement choix);
int examine(Jeu *game, Mouvement pion);
void gagnant(Couleur color);
Couleur gen_tour();
#endif
