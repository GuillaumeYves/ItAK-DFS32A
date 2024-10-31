#ifndef CARTE_H
#define CARTE_H

enum Niveau { NIVEAU_1 = 1, NIVEAU_2, NIVEAU_3 };
enum Couleur { BLANC = 1, GRIS, NOIR, BLEU, ORANGE, ROUGE, VIOLET, ROSE, JAUNE, VERT };
enum Force { FORCE_2 = 2, FORCE_3, FORCE_4, FORCE_5, FORCE_6, FORCE_10 = 10 };

struct Carte {
    enum Niveau niveau;
    enum Couleur couleur;
    enum Force force;
};

#endif