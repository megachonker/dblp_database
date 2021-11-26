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

    tableaux_fiche tableaux_fichee = parse(inputDB);
    printf("tableaux charger");

    // serialize(tableaux_fiche);
    tableaux_fiche coucou = deserialisation();

    printTabmeaux(coucou);

    return 0;
}
