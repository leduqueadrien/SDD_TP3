
#include<stdio.h>
#include "arbre/arbre.h"

void afficherChar(char valeur) {
    printf("%c", valeur);
}

void ConvertionfileEnElement(FILE * file, void * ptr) {
    fscanf(file, "%c", (char *)ptr);
}


int main(int argc, char const *argv[])
{
    if (argc > 1) {
        int code;
        arbre_t * arbre;
        code = creerArbreDepuisFichierNotationAlgebrique(&arbre, argv[1], ConvertionfileEnElement);
        if (code == 0) {
            afficherArbre(arbre, afficherChar);
            libererArbre(&arbre);
        }
    } else {
        printf("aucun nom de fichier n'a ete donnee\n");
    }
    
    return 0;
}
