#include "DataType/listechainee.h"

/// Fonction permetant de creer un chainon d'une liste
pChainon creationchainon(char* key, int value)
{
    pChainon nouveau = malloc(sizeof(Chainon));
    if(PTR_NUL(nouveau))
    {
        ERREUR_ALLOCATION;
        exit(0);
    }

    nouveau->key=key;
    nouveau->value=value;
    nouveau->suivant = NULL;

    return nouveau;
}


/// Insert un nouveau chainon à la fin de la liste en parametre
pChainon insertfin(pChainon pliste, char* key, int value)
{
    if(PTR_NUL(pliste))
    {
        pliste = creationchainon(key, value);
        return pliste;
    }

    pChainon current = pliste;
    pChainon new = creationchainon(key, value);

    /// Nous parcourons la liste tant qu'il y a des suivant
    while(!PTR_NUL(current->suivant))
    {
        current = current->suivant;
    }

    /// S'il n'y en a plus nous en creons un
    current->suivant = new;
    return pliste;
}

/**
 * Insert à la fin d'une liste un couple clef, valeur si aucune valeur déjà présente possède la même clef
 * Retourne :
 * 0 si la valeur à été ajouté
 * 1 si elle existe déjà
 * 2 si pliste vaut null
*/
int insertUnique(pChainon* pliste, char* key, int value) {
    if(PTR_NUL(pliste)) {
        return 2;
    }

    if(PTR_NUL(*pliste)) {
        *pliste = creationchainon(key, value);
        return 0;
    }

    pChainon current = *pliste;

    /// Nous parcourons la liste tant qu'il y a des suivant et que les clefs sont différente
    while(strcmp(current->key, key) != 0 && !PTR_NUL(current->suivant)) {
        current = current->suivant;
    }

    ///On regarde si la raison de l'arret de la boucle est : les clefs sont identique
    if(strcmp(current->key, key) == 0) {
        return 1;
    }

    /// S'il n'y en a plus nous en creons un
    current->suivant = creationchainon(key, value);
    return 0;
}

/**
 * Supprime un chainon en fontion de sa clef
 * Retourne :
 * 0 si la valeur a bien été supprimé
 * 1 si elle n'a pas été trouvé
 * 2 si pliste vaut NULL
 * 3 si key vaut NULL
 */
int retirerChainon(pChainon* pliste, char* key){
    if(PTR_NUL(pliste)) {
        return 2;
    }

    if(PTR_NUL(key)) {
        return 3;
    }
    
    if(PTR_NUL(*pliste)){
        return 1;
    }

    if(strcmp((*pliste)->key, key) == 0){
        retirerDebut(pliste);

        return 0;
    }

    pChainon current = *pliste;

    while(!PTR_NUL(current->suivant) && strcmp(current->suivant->key, key) == 0){
        current=current->suivant;
    }

    /// Cas 1 : on est à la fin, on a pas trouvé, on ne peux pas retirer
    if(PTR_NUL(current->suivant)){
        return 1; 
    }

    ///Cas 2 : on a trouvé
    pChainon remove = current->suivant;
    current->suivant = remove->suivant;
    free(remove);

    return 0;
}

/**
 * Supprime le premier chainon
 * Ne fait rien si pliste vaut NULL ou si la liste est déjà vide
 */
void retirerDebut(pChainon* pliste){
    if(!PTR_NUL(pliste) && !PTR_NUL(*pliste)){
        pChainon remove = (*pliste);
        *pliste = (*pliste)->suivant;
        free(remove);

        return 0;
    }
}

/// Affiche tous les chainons de la liste
void traiterListe(pChainon pliste, char separator)
{
    if(PTR_NUL(pliste))
    {
        LISTE_VIDE;
    }

    pChainon current = pliste;
    while(!PTR_NUL(current))
    {
        printf("(%s, %d)", current->key, current->value);
        if(!PTR_NUL(current->suivant)){
            printf("%c", separator);
        }
        current = current->suivant;
    }
}
