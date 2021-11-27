#include "../main/parsing.h"
#include <stdio.h>
/*
fichier test



*/



// int readdb(FILE * inputDB){
//     tableaux_fiche tableaux_fichee = parse(inputDB);
// }

// int writedb(){
    
// }


int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("PAS BIEN OPTION");
        return 1;
    }

    FILE * inputDB = fopen(argv[1],"r");
    if (!inputDB)
    {
        fprintf(stderr,"imposible d'ouvrire le fichier %s",argv[1]);
    }

    tableaux_fiche * tableaux_fichee;

    printf("azer %s",inputDB);

    switch (argv[2][0])
    {
    case '1':
        printf("Parsing");
        tableaux_fichee = parse("./main/DATA/Serialzed1000.data");
        break;
    case '2':
        printf("Parsing");
        tableaux_fichee = parse(inputDB);
        serialize(*tableaux_fichee);
        break;
    default:
        printf("OWO");
        return 1;
        break;
    }    

    return 0;
}
