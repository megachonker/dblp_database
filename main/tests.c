#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

#define BALISESIZE 200


//int argc, char const *argv[]
int main()
{



    // char ligne[10000] = "<title bibtex=Deciding the {V}apnik-{\v{C}}ervonenkis Dimension is {$\\Sigma^{\text{p}}_3$}-Complete>Deciding the Vapnik-&#268;ervonenkis Dimension in &#8721;<sup>p</sup><sub>3</sub>-Complete.</title>";

    
    // printf("%s",getanchor("title",ligne));
    
    FILE * inputDB = fopen("./DATA/dblp.xml","r");
    if (!inputDB)
    {
        fprintf(stderr,"imposible d'ouvrire le fichier");
    }
    


    char ligne[BALISESIZE];
    int indice_struct = 0;
    // printf("auteur:");
    minimal * fichelocalM = calloc(1,sizeof(minimal));
    fichelocalM->nombre_auteur = 0;
    // tableaux_fiche tableaux_allfiche = calloc(1,sizeof(tableaux_fiche));
    tableaux_fiche tableaux_allfiche;

    
    while (fgets(ligne,BALISESIZE,inputDB))
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
            appendAuteurM(fichelocalM,tmpauteur);
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
        fgets(ligne,BALISESIZE,inputDB);
    }

    return 0;
}
