
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"
#include "../pile/pile.h"
#include "../file/file.h"


arbre_t * creerElementArbre(typeDansArbre valeur, arbre_t * fils, arbre_t * frere) {
	arbre_t * nvElemArbre = (arbre_t *)malloc(sizeof(arbre_t));
	if (nvElemArbre != NULL) {
		(*nvElemArbre).valeur = valeur;
		(*nvElemArbre).fils = fils;
		(*nvElemArbre).frere = frere;
	}
	return nvElemArbre;
}

arbre_t * ajouterFils(arbre_t * arbre, typeDansArbre valeur) {
	arbre_t * nvElemArbre = creerElementArbre(valeur, NULL, NULL);

	if (nvElemArbre != NULL)
		(*arbre).fils = nvElemArbre;

	return nvElemArbre;
}

arbre_t * ajouterFrere(arbre_t * arbre, typeDansArbre valeur) {
	arbre_t * nvElemArbre = creerElementArbre(valeur, NULL, NULL);

	if (nvElemArbre != NULL)
		(*arbre).frere = nvElemArbre;

	return nvElemArbre;
}

int creerArbreDepuisFichierNotationAlgebrique(arbre_t ** arbre, char const * nomFichier, void(*pfConvertion)(FILE *, void *)) {
	FILE * file = fopen(nomFichier, "r");
	int code = 1;

	if (file != NULL && feof(file) == 0) {
		pile_t * pile = initPile(100);
		char car;
		arbre_t * cour;
		
		code = 0;
		cour = creerElementArbre(0, NULL, NULL);
		*arbre = cour;
		empiler(pile, cour);
		if (cour == NULL)
			code = 1;

		while (feof(file) == 0 && code == 0) {
			fscanf(file, "%c", &car);
			switch (car) {
				
			case '(':
				empiler(pile, cour);
				break;

			case ')':
				depiler(pile, &cour);
				break;

			case '+':
				depiler(pile, &cour);
				cour = ajouterFrere(cour, 0);
				empiler(pile, cour);
				if (cour == NULL)
					code = 1;
				break;

			case '*':
				cour = ajouterFils(cour, 0);
				if (cour == NULL)
					code = 1;
				break;

			default:
				(*file)._IO_read_ptr--;
				if (*(*file)._IO_read_ptr != '\0')
					pfConvertion(file, &(*cour).valeur);
				else
					fscanf(file, "%c", &car);
				break;
			}

		}
		libererPile(pile);
		fclose(file);
	}
	return code;
}

void afficherLigne(int nbParent, arbre_t * element, void (*pfAfficher) (typeDansArbre)) {

	for (int i=0; i<nbParent; i++)
		printf("│  ");
	
	if ((*element).frere == NULL && (*element).fils == NULL)
		printf("└── ");
	else
		printf("├── ");
		
	pfAfficher((*element).valeur);
	printf("\n");
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

	if (arbre != NULL) {
		while (continuer == 1) {
			// Parcour en profondeur tant que le dernier fils n'est pas atteint
			while (cour != NULL) {
				// On affiche l'element
				afficherLigne(nbParent, cour, pfAfficher);
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
			if (cour == NULL && estVidePile(pile) == 1)
				continuer = 0;
		}
	} else {
		printf("L'arbre est vide\n");
	}
	libererPile(pile);
}

void libererArbre (arbre_t ** arbre) {
	// Initialisation de la pile permettant de parcourir l'arbre
	pile_t * pile = initPile(100);
	// Booleen qui permet a la boucle principale de s'arreter
	int continuer = 1;
	// Pointeur sur l'arbre qui va parcourir l'arbre
	arbre_t * cour = *arbre;
	arbre_t * prec = NULL;

	
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
	*arbre = NULL;
	libererPile(pile);
}