#include "DataType/hashmap.h"

pMap createHashMap(){
    pMap map = malloc(sizeof(HashMap));
    if(PTR_NUL(map))
    {
        ERREUR_ALLOCATION;
        exit(1);
    }

    map->data = NULL;
    map->size = 0;

    return map;
}

/** Ajoute un couple key, value a la hashmap
 * Retourne true si ma valeur a pu être ajouté, false sinon
*/
bool addHM(pMap map, char* key, int value){
    if(PTR_NUL(map)) {
        return false;
    }

    unsigned long hash = turnToHash(key);

    int result = insertion_ABR(&(map->data), hash, key, value);
    if(result == 0){
        map->size++;
        return true;
    }

    return false;

}

int* getHM(pMap map, char* key){
    if(PTR_NUL(map)) {
        return NULL;
    }

    unsigned long hash = turnToHash(key);
    return chercherHash(map->data, hash, key);
}

/**
 * Supprime de map la valeur key
 * Retourne true si la valeur a été retiré faux sinon
 * La valeur feux peut être retourner dans deux cas :
 * - La valeur n'a pas été trouvé
 * - map ou key ont pour valeur NULL
*/
bool removeHM(pMap map, char* key){
    if(PTR_NUL(map) || PTR_NUL(key)){
        return false;
    }

    int result = supression_hash_ABR(&(map->data), turnToHash(key), key);

    if(result == 0){
        map->size--;
        return true;
    }

    return false;
}

/**
 * Change la valeur de key
 * Retourn true si la valeur a été modifié, false sinon
*/
bool updateHM(pMap map, char* key, int newValue){
    if(PTR_NUL(map) || PTR_NUL(key)) {
        return false;
    }

    int* valuePt = getHM(map, key);

    if(PTR_NUL(valuePt)) {
        return false;
    }

    *valuePt = newValue;
    return true;
}

int sizeHM(pMap map){
    return map->size;
}

void parcourInfixe(pMap map){
    printf("Type HasmMap : {\n");
    parcour_infixe(map->data);
    printf("}\n");
}

void destroyHM(pMap map){
    if(!PTR_NUL(map)){
        desteroyABR(map->data);
        free(map);
    }
}

unsigned long turnToHash(char* key){
    
    unsigned long i = 0;
    for (int j = 0; key[j]; j++)
        i += (key[j]*key[j])-3; ///Ici, ca l'opération est bidon, et peux le rester si on s'en fout de l'efficacité

    return i%CAPACITE;
}
