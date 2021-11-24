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
    
    parse(inputDB);

    return 0;
}
