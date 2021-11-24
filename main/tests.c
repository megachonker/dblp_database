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
    


    char ligne[100];
    int indice_struct = 0;
    // printf("auteur:");
    minimal * fichelocalM = calloc(1,sizeof(minimal));
    // tableaux_fiche tableaux_allfiche = calloc(1,sizeof(tableaux_fiche));
    tableaux_fiche tableaux_allfiche;

    
    while (fgets(ligne,100,inputDB))
    {
        int flagt = 0;

        
        if (!fichelocalM)
        {
            fprintf(stderr,"création de la zone de mémoir pour ficheloca1m compromis calloc");
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
                // printf(" %s,",fichelocalM->titre);
                flagt = 1;
                fichelocalM->titre = fichelocalM->titre;
            }
        }

        if (flagt == 1)
        {
            printM_titre(*fichelocalM);
            printM_liste_auteur(*fichelocalM);
            // printf("%i,,",*fichelocalM)
            appendTabmeaux(&tableaux_allfiche,fichelocalM);
            fichelocalM = calloc(1,sizeof(minimal));
        }
        
        indice_struct++;
        fgets(ligne,100,inputDB);
    }

    return 0;
}
