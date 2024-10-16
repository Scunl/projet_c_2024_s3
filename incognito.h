typedef enum _couleur {BLANC, NOIR} Couleur;
typedef enum _type{CHEVALIER, ESPION} Type;

typedef struct _pion {
    Type type;
    Couleur couleur;
} Pion;

typedef struct {
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