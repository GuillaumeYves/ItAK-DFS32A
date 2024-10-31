#ifndef JOUEUR_H
#define JOUEUR_H

struct Joueur {
    char nom[50];
    struct Carte main[TAILLE_DECK];
};

#endif