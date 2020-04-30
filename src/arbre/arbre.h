
#ifndef ARBRE_H
#define ARBRE_H

#include "../arbre/arbre.h"

typedef char typeDansArbre;

typedef struct arbre
{
    typeDansArbre valeur;
    struct arbre * frere;
    struct arbre * fils;
} arbre_t;


int ajouterFils(arbre_t *, typeDansArbre);
int ajouterFrere(arbre_t *, typeDansArbre);
int creerArbreDepuisFichierNotationAlgebrique(arbre_t *, char *);
void afficherLigne(int, typeDansArbre, void (*) (typeDansArbre));
void afficherArbre(arbre_t *, void (*) (typeDansArbre));
void libererArbre (arbre_t *);


// Deux pointeurs de fonctions :
//      un pour afficher
//      l'autre pour lire dans le fichier

#endif