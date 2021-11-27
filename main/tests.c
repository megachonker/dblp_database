#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"



//int argc, char const *argv[]
int main()
{
    FILE * inputDB = fopen("./DATA/dblp.xml","r");
    if (!inputDB)
    {
        fprintf(stderr,"imposible d'ouvrire le fichier");
    }
    // printTabmeaux(parse(inputDB));


    // tableaux_fiche tableaux_fichee = parse(inputDB);
    // // printf("tableaux charger");

    // serialize(tableaux_fichee);
    tableaux_fiche coucou = deserialisation("./DATA/SerializedStruc.data"); //utiliser des address pour eviter la copie ?? 

    printTabmeaux(coucou);

    return 0;
}
