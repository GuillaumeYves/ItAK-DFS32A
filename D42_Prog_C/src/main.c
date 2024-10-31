#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/carte.h"
#include "../include/deck.h"
#include "../include/joueur.h"
#include "../include/tableau.h"

const char* getCouleurString(int couleur) {
    switch (couleur) {
        case BLANC: return "Blanc";
        case GRIS: return "Gris";
        case NOIR: return "Noir";
        case BLEU: return "Bleu";
        case ORANGE: return "Orange";
        case ROUGE: return "Rouge";
        case VIOLET: return "Violet";
        case ROSE: return "Rose";
        case JAUNE: return "Jaune";
        case VERT: return "Vert";
        default: return "Inconnu";
    }
}

void genererDeck(struct Carte deck[], int size) {
    for (int i = 0; i < size; i++) {
        deck[i].niveau = rand() % 3;
        deck[i].couleur = rand() % 10;
        int forceRandom = rand() % 6;
        deck[i].force = (forceRandom) ? : 10;
    }
}

void initialiserTableau(struct Tableau *tableau) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            tableau->cases[i][j].niveau = -1;
            tableau->cases[i][j].couleur = -1;
            tableau->cases[i][j].force = -1;
        }
    }
}

void afficherTableau(struct Tableau *tableau) {
    printf("Tableau de jeu :\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (tableau->cases[i][j].niveau != -1) {
                printf("| X | ");
            } else {
                printf("|   | ");
            }
        }
        printf("\n");
    }
}

void afficherMain(struct Joueur *joueur) {
    printf("Main de %s :\n", joueur->nom);
    for (int i = 0; i < TAILLE_DECK; i++) {
        if (joueur->main[i].niveau != -1) {
            printf("| %d-%s-%d | ", joueur->main[i].niveau, getCouleurString(joueur->main[i].couleur), joueur->main[i].force);
        }
    }
    printf("\n");
}

int peutPoserCarte(struct Tableau *tableau, struct Carte *carte, int col) {
    int row = carte->niveau - 1;

    if (tableau->cases[row][col].niveau != -1) {
        return 0;
    }

    if (carte->niveau == NIVEAU_2 && (row == 0 || tableau->cases[row - 1][col].niveau == -1)) {
        return 0;
    }
    if (carte->niveau == NIVEAU_3 && (row == 1 || tableau->cases[row - 1][col].niveau == -1)) {
        return 0;
    }

    return 1;
}

struct Carte piocherCarte(struct Carte deck[], int *indexDeck) {
    if (*indexDeck >= TAILLE_DECK) {
        printf("Le deck est vide !\n");
        struct Carte carteVide = {-1, -1, -1};
        return carteVide;
    }
    return deck[(*indexDeck)++];
}

int main() {
    srand(time(NULL));

    struct Carte deck[TAILLE_DECK];
    struct Joueur joueurs[2];
    struct Tableau tableau;
    int indexDeck = 0;

    genererDeck(deck, TAILLE_DECK);
    initialiserTableau(&tableau);

    // Initialiser les joueurs
    for (int i = 0; i < 2; i++) {
        printf("Entrez le nom du joueur %d : ", i + 1);
        scanf("%s", joueurs[i].nom);
        for (int j = 0; j < TAILLE_DECK; j++) {
            joueurs[i].main[j].niveau = -1;
        }
    }

    int tour = 0;
    while (1) {
        int joueurIndex = tour % 2;

        struct Carte cartePiochée = piocherCarte(deck, &indexDeck);
        joueurs[joueurIndex].main[indexDeck % TAILLE_DECK] = cartePiochée;

        afficherMain(&joueurs[joueurIndex]);
        afficherTableau(&tableau);

        printf("%s, choisissez une carte :\n", joueurs[joueurIndex].nom);
        for (int i = 0; i < TAILLE_DECK; i++) {
            if (joueurs[joueurIndex].main[i].niveau != -1) {
                printf("%d: %d-%s-%d\n", i, joueurs[joueurIndex].main[i].niveau, getCouleurString(joueurs[joueurIndex].main[i].couleur), joueurs[joueurIndex].main[i].force);
            }
        }
        printf("-1 pour passer.\n");

        int carteChoisie;
        scanf("%d", &carteChoisie);

        if (carteChoisie == -1) {
            tour++;
            continue;
        }

        if (carteChoisie < 0 || carteChoisie >= TAILLE_DECK || joueurs[joueurIndex].main[carteChoisie].niveau == -1) {
            printf("Carte invalide, veuillez réessayer.\n");
            continue;
        }

        struct Carte carteAJouer = joueurs[joueurIndex].main[carteChoisie];

        printf("Choisissez une colonne (0-%d) pour jouer la carte : ", COLS - 1);
        int col;
        scanf("%d", &col);

        if (col < 0 || col >= COLS || !peutPoserCarte(&tableau, &carteAJouer, col)) {
            printf("Vous ne pouvez pas poser cette carte, veuillez réessayer.\n");
            continue;
        }

        tableau.cases[carteAJouer.niveau - 1][col] = carteAJouer;
        joueurs[joueurIndex].main[carteChoisie].niveau = -1;

        tour++;
        printf("État de la partie après le tour de %s :\n", joueurs[joueurIndex].nom);
        afficherMain(&joueurs[0]);
        afficherMain(&joueurs[1]);
        afficherTableau(&tableau);

        if (indexDeck >= TAILLE_DECK) {
            printf("Fin de la partie !\n");
            break;
        }
    }

    return 0;
}
