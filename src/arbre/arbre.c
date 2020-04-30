
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"
#include "../pile/pile.h"
#include "../file/file.h"

int ajouterFils(arbre_t * arbre, typeDansArbre valeur) {
	int code = 1;
	arbre_t * nvElemArbre = (arbre_t *)malloc(sizeof(arbre_t));

	if (nvElemArbre != NULL) {
		code = 0;
		(*nvElemArbre).valeur = valeur;
		(*arbre).fils = nvElemArbre;
		(*arbre).frere = NULL;
	}
	return code;
}

int ajouterFrere(arbre_t * arbre, typeDansArbre valeur) {
	int code = 1;
	arbre_t * nvElemArbre = (arbre_t *)malloc(sizeof(arbre_t));

	if (nvElemArbre != NULL) {
		code = 0;
		(*nvElemArbre).valeur = valeur;
		(*arbre).fils = NULL;
		(*arbre).frere = nvElemArbre;
	}
	return code;
}

int creerArbreDepuisFichierNotationAlgebrique(arbre_t * arbre, char * nomFichier) {
	FILE * file = fopen(nomFichier, "r");
	pile_t pile = initPile(100);

	if (file != NULL) {
		int continuer = 1;
		char caract;

		while (continuer == 1) {
			;

			
		}

	} else {
		printf("Impossible d'ouvrir le fichier \"%s\"\n", nomFichier);
	}
}

void afficherLigne(int nbParent, typeDansArbre valeur, void (*pfAfficher) (typeDansArbre)) {

	for (int i=0; i<nbParent; i++)
		printf("│  ");
	printf("├── ");
	pfAfficher(valeur);
}

void afficherArbre(arbre_t * arbre, void (*pfAfficher) (typeDansArbre)) {
	// Initialisation de la pile permettant de parcourir l'arbre
	pile_t * pile = initPile(100);
	// Booleen qui permet a la boucle principale de s'arreter
	int continuer = 1;
	// Pointeur sur l'arbre qui va parcourir l'arbre
	arbre_t * cour = arbre;
	// Compte le nombre de parent qu'a l'element pointer par cour
	int nbParent = 0;

	
	while (continuer == 1) {
		// Parcour en profondeur tant que le dernier fils n'est pas atteint
		while (cour != NULL) {
			// On affiche l'element
			afficherLigne(nbParent, (*cour).valeur, pfAfficher);
			nbParent++;
			// On par sur le fils
			empiler(pile, cour);
			cour = (*cour).fils;
		}
		// On recupere le dernier element parcouru
		depiler(pile, &cour);
		nbParent--;
		// On par sur le frere
		cour = (*cour).frere;
		// Si il existe, on affiche l'element
		if (cour != NULL)
			afficherLigne(nbParent, (*cour).valeur, pfAfficher);
		else if (estVidePile(pile) == 1)
			continuer = 0;
	}
}

void libererArbre (arbre_t * arbre) {
	// Initialisation de la pile permettant de parcourir l'arbre
	pile_t * pile = initPile(100);
	// Booleen qui permet a la boucle principale de s'arreter
	int continuer = 1;
	// Pointeur sur l'arbre qui va parcourir l'arbre
	arbre_t * cour = arbre;
	arbre_t * prec;

	
	while (continuer == 1) {
		// Parcour en profondeur tant que le dernier fils n'est pas atteint
		while (cour != NULL) {
			// On par sur le fils
			empiler(pile, cour);
			cour = (*cour).fils;
		}
		// On par sur le frere
		depiler(pile, &cour);
		// On libere l'element depiler
		prec = cour;
		cour = (*cour).frere;
		free(prec);

		// Si il existe, on affiche l'element
		if (cour == NULL && estVidePile(pile) == 1)
			continuer = 0;
	}
}