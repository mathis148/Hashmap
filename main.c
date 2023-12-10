/*! 
\mainpage Hashmap project
\author : Mathis Contassot
\file main.c
\author Mathis Contassot
\version 2.4
\date 8/12/2023
\brief Hashmap
*/


#include "main.h"

int main(){
    ///Ce scripte utilise des macros pour effectuer une opération sur hashmap et afficher un résultat, voir incude/main.h

    HashMap* map = createHashMap();

    printf("\n---------------------------------------------\nAjout\n---------------------------------------------\n\n");
    BT_ADD_HM(map, "Prof", 69)
    BT_ADD_HM(map, "Mathis", 20)
    BT_ADD_HM(map, "Lili",   5 )
    BT_ADD_HM(map, "Cams",   6 )
    BT_ADD_HM(map, "Théo", 18)
    BT_ADD_HM(map, "Alban", 18)

    parcourInfixe(map);

    printf("Size of map : %d\n", sizeHM(map));
    printf("Value of Mathis in map : %d\n", *getHM(map, "Mathis"));

    printf("\n---------------------------------------------\nSupression\n---------------------------------------------\n\n");
    BT_REMOVE_HM(map, "Théo")
    BT_REMOVE_HM(map, "Cams")
    parcourInfixe(map);

    printf("\n---------------------------------------------\nMise à jour\n---------------------------------------------\n\n");
    BT_UPDATE_HM(map, "Mathis", 99)
    BT_UPDATE_HM(map, "Lili", 50)
    BT_UPDATE_HM(map, "Lili-Rose", -99)
    parcourInfixe(map);

    printf("Destruction avec libération de mémoire de la HashMap ...\n");
    destroyHM(map);
    printf("Fin du prog\n");

    return 0;
}
