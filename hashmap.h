#ifndef HASHMAP
#define HASHMAP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ABR.h"

#define PTR_NUL(ptr) (ptr == NULL)
#define ERREUR_ALLOCATION printf("\nErreur d'allocation")

#define CAPACITE 50000;
#define MULTIPLICATEUR_TAILLE 0.2f; //Utilisé pour agrandire la taille de la hashmap

typedef struct{
    int size;
    pArbre data;
}HashMap;

typedef HashMap* pMap;

pMap createHashMap();

bool addHM(pMap map, char* key, int value);
bool removeHM(pMap map, char* key);
bool updateHM(pMap map, char* key, int newValue);

int* getHM(pMap map, char* key); 
int sizeHM(pMap map);

void parcourInfixe(pMap map);
void destroyHM(pMap map);

unsigned long turnToHash(char* key);

#endif