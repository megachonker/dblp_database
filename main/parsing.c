#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct minimal
{
    char * titre;
    char ** liste_auteur;
    int nombre_auteur;
}minimal;


void printM_titre(minimal OwO){
    printf("titre: %s\n",OwO.titre);
}
void printM_liste_auteur(minimal UwU){
    printf("auteurs: ");
    for (size_t i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s ",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf(",");
    }
    printf("\n");
}


char * getanchor(char * recherche, char * ligne){
    char critaire[20] = "<";
    strcat(critaire,recherche);
    if(strstr(ligne,critaire)){ //slow ?
        char * start = strchr(ligne,'>') +1;
        int diff = strcspn(start,"<");
        char * out  = calloc(1,diff);
        if (!out)
        {
            fprintf(stderr,"pas de match");
            return NULL;
        }
        memcpy(out,start,diff);
        return out;
    }
    return NULL;
}

void appendAuteurM(char ** liste_auteur,int indice, char * nomsauteur){
    char ** addrListeauteur = realloc(liste_auteur,sizeof(minimal)*(indice+1));
 
    if (!addrListeauteur)
    {
        fprintf(stderr,"appendAuteurM: allocation imposible");
    }else if (liste_auteur != addrListeauteur)
    {
        liste_auteur = addrListeauteur;
    }
    liste_auteur[indice] = nomsauteur;
}