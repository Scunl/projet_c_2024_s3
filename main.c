#include "incognito.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*la fonction principale du jeu 

initialise la partie, gère les options en ligne de commande et le déroulement de la partie 

Arguments:
argc: nombre d'arguments en ligne de commande
argv: tableau d'arguments en ligne de commande 

Commandes:
"-a": Affiche le jeu en mode ASCII
"-g": Indique que le mode graphique est indisponible, ansi l'affichage ASCII est utilisé par defaut
"-s [fichier]": Active la sauvegrade des mouvements dans un fichier 
"-t": Active le mode triche pour révéler les espions adverses en majuscules 
"-c [fichier]": charge une partie sauvegardée à partir d'un fichier 

Fonctionnalitées principales: 
Gestion du tour
Déplacmements des pions 
Règles de mouvement
Examine des pions ennemis
Déclaration de la victoire

valeurs de retour:
renvoie 0 si le jeu se termine correctement, 1 si y'a une erreur 
*/
int main(int argc, char const *argv[]) {
    Jeu game;
    Mouvement pion;
    Case *espion = init_plateau(TAILLE, &game);
    printf("%d %d %d %d\n", espion[0].x, espion[0].y, espion[1].x, espion[1].y);
    Couleur tour_initial = gen_tour();
    Couleur tour = tour_initial;
    int partie = 1;
    int save = 0;
    int triche = 0;
    int nb_coups = 0;
    FILE *saved_file = NULL;
    FILE *load_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            printf("Affichage en mode ASCII\n");
        }
        if (strcmp(argv[i], "-g") == 0) {
            printf("La partie graphique est indisponible. Mode ASCII sera "
                   "l'affichage par défaut\n");
        }
        if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            save = 1;
            saved_file = fopen(argv[++i], "a");
            if (!saved_file) {
                perror("Erreur d'ouverture du fichier de sauvegarde");
                return 1;
            }
        }
        if (strcmp(argv[i], "-t") == 0) {
            triche = 1;
            printf("La triche est activiée est vous pouvez voir les "
                   "coordonées des espions en majuscule\n");
        }

        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            load_file = fopen(argv[++i], "r");
            if (!load_file) {
                perror("Erreur d'ouverture du fichier de chargement");
                return 1;
            }
        }
    }

    show_tab(TAILLE, &game, triche);
    while (partie) {
        do {
            printf("=======Appuyez sur n'importe quelle touche pour "
                   "arrêter la "
                   "partie=======\n");
            if (tour == BLANC)
                printf("C'est au tour du joueur Blanc\n");
            else
                printf(" > C'est au tour du joueur Noir\n");
            printf("  >  Séléctionnez les coordonées du pion que vous "
                   "souhaitez "
                   "déplacer\n  > ");
            pion.depart = parse();
            if (pion.depart.x == -2 || pion.depart.y == -2) {
                printf("Fin de partie\n");
                partie = 0;
                break;
            }
            if (pion.depart.x == -1 || pion.depart.y == -1) {
                while (getchar() != '\n') {
                }
                printf("Coordonnées invalides, veuillez réessayer.\n");
                continue;
            }
        } while (
            ((pion.depart.x >= TAILLE || pion.depart.x < 0 ||
              pion.depart.y >= TAILLE || pion.depart.y < 0) ||
             (game.plateau[pion.depart.x][pion.depart.y].couleur != tour)));

        if (!partie)
            break;
        do {
            printf("  > Séléction du pion en x : %d et y : %d\n", pion.depart.x,
                   pion.depart.y);

            show_tab(TAILLE, &game, triche);
            printf("    >   Vers quelle case voulez-vous effectuer votre coup "
                   "?\n    > ");
            pion.arrivee = parse();
            if (pion.arrivee.x == -1 || pion.arrivee.y == -1) {
                while (getchar() != '\n') {
                    printf("Coordonnées invalides, veuillez réessayer.\n");
                    continue;
                }
            }
        } while (
            ((pion.depart.x >= TAILLE || pion.depart.x < 0 ||
              pion.depart.y >= TAILLE || pion.depart.y < 0) ||
             (game.plateau[pion.depart.x][pion.depart.y].couleur != tour) ||
             (abs(pion.depart.x - pion.arrivee.x) > 1) ||
             abs(pion.depart.y - pion.arrivee.y) > 1) ||
            (tour == BLANC && pion.arrivee.x == TAILLE - 1 &&
             pion.arrivee.y == 0) ||
            (tour == NOIR && pion.arrivee.x == 0 &&
             pion.arrivee.y == TAILLE - 1));

        // if (nb_coups < MAX_COUPS) {
        //     coups[nb_coups++] = pion; Chargement
        // }
        if (save) {
            sauvegarde_deroule(saved_file, pion, nb_coups, tour, espion);
        }
        nb_coups++;

        if ((game.plateau[pion.arrivee.x][pion.arrivee.y].couleur == VIDE)) {
            shift(&game, pion);
        } else if (game.plateau[pion.arrivee.x][pion.arrivee.y].type !=
                   CHATEAU) {
            if (examine(&game, pion)) {
                if (game.plateau[pion.depart.x][pion.depart.y].type == ESPION &&
                    game.plateau[pion.arrivee.x][pion.arrivee.y].couleur !=
                        tour) {
                    game.plateau[pion.depart.x][pion.depart.y].couleur = VIDE;
                    gagnant((tour == BLANC ? NOIR : BLANC));
                    printf("Et en plus, votre chevalier s'est fait "
                           "empoisonné...\n");
                    partie = 0;
                } else if ((game.plateau[pion.depart.x][pion.depart.y].type ==
                            CHEVALIER) &&
                           (game.plateau[pion.arrivee.x][pion.arrivee.y].type ==
                            ESPION) &&
                           (game.plateau[pion.arrivee.x][pion.arrivee.y]
                                .couleur != tour)) {
                    gagnant(tour);
                    printf("Ils ont découvert l'esion adverse !\n");
                    partie = 0;
                } else {
                    if (game.plateau[pion.arrivee.x][pion.arrivee.y].couleur ==
                        tour)
                        continue;
                    game.plateau[pion.depart.x][pion.depart.y].couleur = VIDE;
                    printf("Et en plus, votre chevalier s'est fait "
                           "empoisonné...\n");
                }
                show_tab(TAILLE, &game, triche);
            }
        } else {
            if (game.plateau[pion.depart.x][pion.depart.y].couleur !=
                game.plateau[pion.arrivee.x][pion.arrivee.y].couleur)
                partie = 0;
            printf(
                "Les %s ont gagné la partie après avoir atteint le chateau !\n",
                (tour == BLANC ? "blancs" : "noirs"));
        }
        show_tab(TAILLE, &game, triche);

        if ((tour == NOIR) & (pion.arrivee.x == TAILLE - 1) &
            (pion.arrivee.y == 0)) {
            gagnant(NOIR);
            partie = 0;
        }
        if ((tour == BLANC) & (pion.arrivee.x == 0) &
            (pion.arrivee.y == TAILLE - 1)) {
            gagnant(BLANC);
            partie = 0;
        }

        tour = (tour == NOIR) ? BLANC : NOIR;
    }

    return 0;
}
