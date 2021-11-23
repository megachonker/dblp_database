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
    while (fgets(ligne,100,inputDB))
    {
        
        minimal fichelocalM;
        char * tmpauteur = getanchor("author",ligne);
        if (tmpauteur)
        {
            // printf(" %s,",tmpauteur);
            appendAuteurM(fichelocalM.liste_auteur,indice_struct,tmpauteur);
        }else{
            fichelocalM.titre = getanchor("title",ligne);
            if (fichelocalM.titre)
            {
                fichelocalM.titre = fichelocalM.titre;
                // printf("\ntitre: %s\n",fichelocalM.titre);
            }
        }

        indice_struct++;
        fgets(ligne,100,inputDB);
    }

    return 0;
}
