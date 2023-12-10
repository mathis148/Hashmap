#ifndef mainTest
#define mainTest

#include "DataType/hashmap.h"

//Macro pour effectuer les testes rapidement
#define SUCESS "Oui"
#define ERROR  "Non"

#define BT_ADD_HM(map, key, value) printf("Ajout de %s réussit ? %s\n", key, addHM(map, key, value)==true ? SUCESS:ERROR);
#define BT_REMOVE_HM(map, key) printf("Supression de %s réussit ? %s\n", key, removeHM(map, key)==true ? SUCESS:ERROR);
#define BT_UPDATE_HM(map, key, newValue) printf("Mise à joure de %s réussit ? %s\n", key, updateHM(map, key, newValue)==true ? SUCESS:ERROR);

#endif