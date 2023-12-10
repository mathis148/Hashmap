#ifndef ABRE_BR
#define ABRE_BR

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "listechainee.h"

#define PTR_NUL(ptr) (ptr == NULL)
#define ERREUR_ALLOCATION printf("\nErreur d'allocation")

/// Definition des macros utilisé dans ce fichier
#define ARBRE_VIDE printf("\nL'arbre est vide !")

// Creation de la structure de l'Abre utilise pour les ABR et aussi les AVL
typedef struct arbre
{
    unsigned long hash;
    pChainon values;
    struct arbre* fg;
    struct arbre* fd;
}Arbre;

typedef Arbre* pArbre;


/// Déclaration des fonctions
pArbre creerArbre(unsigned long hash, char* key, int value);
int insertion_ABR(pArbre* aPt, unsigned long hash, char* key, int value);

int supression_hash_ABR(pArbre* aPt, unsigned long hash, char* key);
pArbre supprimerNoeud(pArbre a);

bool existe_fg(pArbre a);
bool existe_fd(pArbre a);

void ajouter_fg(pArbre a, unsigned long hash, char* key, int value);
void ajouter_fd(pArbre a, unsigned long hash, char* key, int value);
void traiter_noeud(pArbre a);
void parcour_infixe(pArbre a);
void parcour_infixe_debug(pArbre a);

void desteroyABR(pArbre a);

int* chercherHash(pArbre a, unsigned long hash, char* key);

#endif
