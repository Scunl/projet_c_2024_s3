#include "incognito.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    Jeu game;
    Mouvement pion;
    init_plateau(TAILLE, &game);
    show_tab(TAILLE, &game);
    Couleur tour_initial = gen_tour();
    Couleur tour = tour_initial;
    int partie = 1;
    int save = 0;
    int nb_coups = 0;
    FILE *saved_file = NULL;
    FILE *load_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            printf("Affichage en mode ASCII\n");
        } else if (strcmp(argv[i], "-g") == 0) {
            printf("La partie graphique est indisponible. Mode ASCII sera "
                   "l'affichage par défaut\n");
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            save = 1;
            saved_file = fopen(argv[++i], "w");
            if (!saved_file) {
                perror("Erreur d'ouverture du fichier de sauvegarde");
                return 1;
            }
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            load_file = fopen(argv[++i], "r");
            if (!load_file) {
                perror("Erreur d'ouverture du fichier de chargement");
                return 1;
            }
        } else {
            printf("Option non reconnue: %s\n", argv[i]);
            return 1;
        }
    }

    while (partie) {
        do {
            printf("=======Appuyez sur n'importe quelle touche pour arrêter la "
                   "partie=======\n");
            if (tour == BLANC)
                printf("C'est au tour du joueur Blanc\n");
            else
                printf(" > C'est au tour du joueur Noir\n");
            printf(
                "  >  Séléctionnez les coordonées du pion que vous souhaitez "
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
            show_tab(TAILLE, &game);
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

        if (game.plateau[pion.depart.x][pion.depart.y].type == ESPION) {
        }

        if ((game.plateau[pion.arrivee.x][pion.arrivee.y].couleur == VIDE)) {
            shift(&game, pion);
        } else {
            if (examine(&game, pion)) {
                printf("1 - %d : %d\n2 - %d : %d\n",
                       game.plateau[pion.depart.x][pion.depart.y].type,
                       game.plateau[pion.depart.x][pion.depart.y].couleur,
                       game.plateau[pion.arrivee.x][pion.arrivee.y].type,
                       game.plateau[pion.arrivee.x][pion.arrivee.y].couleur);
                if ((game.plateau[pion.arrivee.x][pion.arrivee.y].couleur !=
                     tour) &&
                    (game.plateau[pion.depart.x][pion.depart.y].type !=
                     ESPION)) {

                    gagnant(tour);
                    partie = 0;
                } else {
                    if (tour == BLANC)
                        printf("Votre espion est mort et les noirs gagnent la "
                               "partie !\n");
                    else
                        printf("Votre espion est mort et les blancs gagnent la "
                               "partie !\n");
                    partie = 0;
                }
            } else if (game.plateau[pion.arrivee.x][pion.arrivee.y].couleur !=
                       tour) {
                game.plateau[pion.depart.x][pion.depart.y].couleur = VIDE;
            } else {
                printf("Vous ne pouvez pas vérifier le type de votre propre "
                       "pion\n");
                show_tab(TAILLE, &game);
                continue;
            }
        }
        show_tab(TAILLE, &game);
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
    if (save) {
        sauvegarde_deroule(saved_file, &game, tour_initial, tour, &pion,
                           nb_coups);
        fclose(saved_file);
    }
    return 0;
}
