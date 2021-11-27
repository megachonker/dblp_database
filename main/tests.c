#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "creation_sommets_G.h"

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\


tableaux_fiche default_loading_Struct(){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    return deserialisation(inputDB);
}

int main()
{
    tableaux_fiche mesfiches = default_loading_Struct();
    creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);

    return 0;
}
