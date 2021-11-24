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

    tableaux_fiche tableaux_fiche = parse(inputDB);

    for (int i = 0; i < tableaux_fiche.taille; i++)
    {
            printM((*(tableaux_fiche.fiche[i])));

    }
    

    return 0;
}
