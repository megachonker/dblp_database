#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>


//int argc, char const *argv[]
int main()
{
    FILE * inputDB = fopen("./DATA/dblp.xml","r");
    if (!inputDB)
    {
        fprintf(stderr,"imposible d'ouvrire le fichier");
    }
    


    char ligne[100];
    int indice_struct = 0;
    // printf("auteur:");
    minimal * fichelocalM = calloc(1,sizeof(minimal));
    tableaux_fiche ** tableaux_allfiche = calloc(1,sizeof(tableaux_fiche));
    tableaux_allfiche;
    while (fgets(ligne,100,inputDB))
    {
        int flagt = 0;

        
        if (!fichelocalM)
        {
            fprintf("création de la zone de mémoir pour ficheloca1m compromis calloc");
        }
        
        char * tmpauteur = getanchor("author",ligne);
        if (tmpauteur)
        {
            // printf(" %s,",tmpauteur);
            appendAuteurM(fichelocalM->liste_auteur,indice_struct,tmpauteur);
        }else{
            fichelocalM->titre = getanchor("title",ligne);
            if (fichelocalM->titre)
            {
                flagt = 1;
                fichelocalM->titre = fichelocalM->titre;
            }
        }

        if (flagt == 1)
        {
            tableaux_allfiche;
            minimal * fichelocalM = calloc(1,sizeof(minimal));
        }
        

        indice_struct++;
        fgets(ligne,100,inputDB);
    }

    return 0;
}
