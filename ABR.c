#include "DataType/ABR.h"


/// Fonction permetant de creer le noeud d'un arbre et de retourner son adresse
pArbre creerArbre(unsigned long hash, char* key, int value)
{
    pArbre nouveau = malloc(sizeof(Arbre));
    if(PTR_NUL(nouveau))
    {
        ERREUR_ALLOCATION;
        exit(1);
    }

    /// Création liste
    nouveau->values = creationchainon(key, value);

    nouveau->hash=hash;
    nouveau->fg = NULL;
    nouveau->fd = NULL;

    return nouveau;
}

/// Ajoute un fils gauche au chainon mis en parametre
void ajouter_fg(pArbre a, unsigned long hash, char* key, int value)
{
    if(PTR_NUL(a))
    {
        ARBRE_VIDE;
    }

    pArbre nouveau = creerArbre(hash, key, value);
    a->fg = nouveau;    
}

/// Ajoute un fils droit au chainon mis en parametre
void ajouter_fd(pArbre a, unsigned long hash, char* key, int value)
{
    if(PTR_NUL(a))
    {
        ARBRE_VIDE;
    }

    if(!existe_fd(a))
    {
        pArbre nouveau = creerArbre(hash, key, value);
        a->fd = nouveau;
    }
}

/**
 * Insert dans l'abr, si le hash existe déja, n'ajoute a la liste
 * Retourne :
 * 0 si la valeur a été ajouté
 * 1 si la valeur n'a pas été ajouté car elle est déjà présente
 * 2 si aPt vaut NULL
 * 3 si key vaut NULL
*/
int insertion_ABR(pArbre* aPt, unsigned long hash, char* key, int value)
{
    if(PTR_NUL(aPt)) {
        return 2;
    }

    if(PTR_NUL(key)) {
        return 3;
    }

    pArbre a = *aPt;
    if(PTR_NUL(a)) {
        *aPt = creerArbre(hash, key, value);
        return 0;
    }
    
    /// On compare toutes les premier champs
    if(hash == a->hash) {
        return insertUnique(&(a->values), key, value) == 0 ? 0 : 1;
        
    }else if(hash < a->hash) {
        return insertion_ABR(&(a->fg), hash, key, value);
    
    } else {
        return insertion_ABR(&(a->fd), hash, key, value);
    }

    return 1;
}

/**
 * Fonction permetant de supprimer un clef a partir de son hash
 * Si la clef n'est pas trouvé ou vaut NULL retourne NULL
 * Sinon retourne l'arbre avec la clef retiré
 * On notera que cette fonction ne retire pas de noeuds si il existe une deuxième clef avec le même hash dans l'arbre
 * Retourne :
 * 0 si la clef a pu être supprimer
 * 1 si la clef n'a pas été supprimé
 * 2 si a vaut NULL
 * 3 si key vaut NULL
*/
int supression_hash_ABR(pArbre* aPt, unsigned long hash, char* key){
    if(PTR_NUL(aPt)){
        return 2;
    }

    if(PTR_NUL(key)){
        return 3;
    }

    pArbre a = *aPt;
    if(PTR_NUL(a)){
            return 1;
    }

    if(hash == a->hash){
        ///Vérification il n'y pas d'element, ce n'est pas normal, on retire le noeud
        if(PTR_NUL(a->values)){
            *aPt = supprimerNoeud(a);
            return 1;
        
        ///Il n'y a qu'un element dans la liste si c'est le bon on le supprime
        }else if(PTR_NUL(a->values->suivant) && strcmp(a->values->key, key) == 0){
            *aPt = supprimerNoeud(a);
            return 0;
        
        ///Il y a plus d'un element, on le retire de la liste
        }else{
            /** Ici on ne prends pas en compte les erreurs, on ne veut que 0 ou 1
             * Si la valeur de retour vaut 0, on retourne 0
             * Sinon on retourne 1
            */
            return retirerChainon(&(a->values), key)==0 ? 0 : 1;
        }

    }else if(hash < a->hash) {
        return supression_hash_ABR(&(a->fg), hash, key);
    } else {
        return supression_hash_ABR(&(a->fd), hash, key);
    }

    return 1;
}

/**
 * Cette fonction retire la racine de l'arbre passé en paramètre
 * Retourne le nouvel arbre
*/
pArbre supprimerNoeud(pArbre a){
    if(PTR_NUL(a)){
        return NULL;
    }

    /// On vide la liste de clef/valeur
    while(!PTR_NUL(a->values)){
        retirerDebut(&(a->values));
    }

    ///Feuille
    if(PTR_NUL(a->fg) && PTR_NUL(a->fd)){
        free(a);
        return NULL;
    
    ///Fils gauche seulement
    }else if(!PTR_NUL(a->fg) && PTR_NUL(a->fd)){
        pArbre suivant = a->fg;
        free(a);
        return suivant;

    ///FIls droit seulement
    }else if(PTR_NUL(a->fg) && !PTR_NUL(a->fd)){
        pArbre suivant = a->fd;
        free(a);
        return suivant;

    ///Deux fils
    }else{
        ///On cherche le plus petit fils droit
        pArbre newRacine = a->fd;

        ///Si c'est le fils droite de a
        if(PTR_NUL(newRacine->fg)){
            newRacine->fg = a->fg;
            free(a);
            return newRacine;
        }

        while(!PTR_NUL(newRacine->fg->fg)){
            newRacine = newRacine->fg;
        }

        pArbre pere = newRacine;
        newRacine = newRacine->fg;

        pere->fg = newRacine->fd;

        newRacine->fg = a->fg;
        newRacine->fd = a->fd;

        free(a);
        return newRacine;
    }
}

/// Retourne l'existance d'un fils gauche
bool existe_fg(pArbre a)
{
    return PTR_NUL(a) && PTR_NUL(a->fg);
}

/// Retourne l'existance d'un fils droit
bool existe_fd(pArbre a)
{
    return PTR_NUL(a) && PTR_NUL(a->fd);
}

/// Affiche un noeud specifique de l'arbre de la meme maniere qu'une liste
void traiter_noeud(pArbre a)
{
    if(PTR_NUL(a))
    {
        ARBRE_VIDE;
    }
    traiterListe(a->values, ',');
    printf("\n");
}

/// Fonction permetant de retourner les valeurs de l'arbre de façon croissante
void parcour_infixe(pArbre a)
{
    if(!PTR_NUL(a))
    {
        parcour_infixe(a->fg);
        traiter_noeud(a);
        parcour_infixe(a->fd);
    }
}

/// Fonction permetant de retourner les valeurs de l'arbre de façon croissante
void parcour_infixe_debug(pArbre a)
{
    if(!PTR_NUL(a))
    {
        parcour_infixe_debug(a->fg);
        printf("%lu ", a->hash);
        parcour_infixe_debug(a->fd);
    }
}

int* chercherHash(pArbre a, unsigned long hash, char* key){
    if(PTR_NUL(a)){
        return NULL;
    }

    if(hash == a->hash){
        ///Recherche dans le tableau
        pChainon pt = a->values;
        while(!PTR_NUL(pt)){
            if(strcmp(pt->key, key) == 0){
                return &(pt->value);
            }
            pt=pt->suivant;
        }

    }else if(hash < a->hash) {
        return chercherHash(a->fg, hash, key);
    } else {
        return chercherHash(a->fd, hash, key);
    }

    return NULL;
}

/**
 * Méthode qui enlève tous les noeuds d'un arbre
*/
void desteroyABR(pArbre a){
    if(!PTR_NUL(a)){
        desteroyABR(a->fg);
        desteroyABR(a->fd);
        supprimerNoeud(a);
    }
}
