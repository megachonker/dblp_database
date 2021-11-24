#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsing.h"


#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg)\
}\


// typedef struct minimal
// {
//     char * titre;
//     char ** liste_auteur;
//     int nombre_auteur;
// }minimal;

// typedef struct tableaux_fiche
// {
//     minimal ** address;
//     int taille;
// }tableaux_fiche;


void printM_titre(minimal OwO){
    printf("titre: %s\n",OwO.titre);
}
void printM_liste_auteur(minimal UwU){
    printf("auteurs: ");
    for (int i = 0; i < UwU.nombre_auteur; i++)
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

void appendTabmeaux(tableaux_fiche * table, minimal * a_ajouter){
    // *table->address;
    // table->address;
    void * addrListFiche = realloc(table->address,sizeof(tableaux_fiche)*(table->taille+1));
 
    if (!addrListFiche)
    {
        fprintf(stderr,"appendTabmeaux: allocation imposible");
    }else if (table != addrListFiche)
    {
        table->address = addrListFiche;
    }
    table->address[table->taille] = a_ajouter;
    table->taille++;
    
}