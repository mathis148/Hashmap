#ifndef LISTE_CHAINEE
#define LISTE_CHAINEE

// Importation des libraries utilisées
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Creation de constantes
#define PTR_NUL(ptr) (ptr == NULL)
#define ERREUR_ALLOCATION printf("\nErreur d'allocation")

// Definition des macros utilisé dans ce fichier
#define LISTE_VIDE printf("\nLa liste est vide")

//// Crée la structure du chainon
typedef struct chainon
{
    char* key;
    int value;
    struct chainon* suivant;
}Chainon;

typedef Chainon* pChainon;

//// Établie les définitions des fonctions
pChainon creationchainon(char* key, int value);
pChainon insertfin(pChainon pliste, char* key, int value);

int insertUnique(pChainon* pliste, char* key, int value);

int retirerChainon(pChainon* pliste, char* key);
void retirerDebut(pChainon* pliste);

void traiterListe(pChainon pliste, char end);




#endif