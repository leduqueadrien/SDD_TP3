
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


arbre_t * creerElementArbre(typeDansArbre, arbre_t *, arbre_t *);
arbre_t * ajouterFils(arbre_t *, typeDansArbre);
arbre_t * ajouterFrere(arbre_t *, typeDansArbre);
int creerArbreDepuisFichierNotationAlgebrique(arbre_t **, char const *, void(*)(FILE *, void *));
void afficherLigne(int, arbre_t *, void (*) (typeDansArbre));
void afficherArbre(arbre_t *, void (*) (typeDansArbre));
void libererArbre (arbre_t **);


// pointeurs de fonctions :
//		un pour afficher
//		un pour convertir la chaine de caractere en element de type dans l'arbre
//		un pour liberer la memoire de l'élément

#endif