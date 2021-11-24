#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsing.h"

#define BALISESIZE 1000


#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\




void printM_titre(minimal OwO){
    printf("titre: %s\n",OwO.titre);
}
void printM_liste_auteur(minimal UwU){
    printf("auteurs: ");
    for (int i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf(", ");
    }
    printf(".\n");
}

void printM(minimal OwU){
    printM_titre(OwU);
    printM_liste_auteur(OwU);   
}

void printTabmeaux(tableaux_fiche UwO){

    for (size_t i = 0; i < UwO.taille; i++)
    {
        printM(*(UwO.address[i]));
    }
}

//fonction qui cherche le string dans ldes <>

char * getanchor(char * recherche, char * ligne){
    char critaire[20] = "<";
    strcat(critaire,recherche);
    if(strstr(ligne,critaire)){ //slow ?
        char * start = strchr(ligne,'>');
        exitIfNull(start,"getanchor: pas de start")
        start++;
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

void appendAuteurM(minimal * mafiche,char * nomsauteur){
    void * addrListeauteur = realloc(mafiche->liste_auteur,sizeof(minimal)*(mafiche->nombre_auteur+1));
 
    if (!addrListeauteur)
    {
        fprintf(stderr,"appendAuteurM: allocation imposible");
    }else if (mafiche->liste_auteur != addrListeauteur)
    {
        mafiche->liste_auteur = addrListeauteur;
    }
    mafiche->liste_auteur[mafiche->nombre_auteur] = nomsauteur;
    mafiche->nombre_auteur++;
}

void appendTabmeaux(tableaux_fiche * table, minimal * a_ajouter){

    void * addrListFiche = realloc(table->address,sizeof(tableaux_fiche)*(table->taille+1));
 
    if (!addrListFiche)
    {
        fprintf(stderr,"appendTabmeaux: allocation imposible");
        exit(1);
    }else if (table != addrListFiche)
    {
        table->address = addrListFiche;
    }
    table->address[table->taille] = a_ajouter;
    table->taille++;   
}

void parse(FILE * inputDB){

    char ligne[BALISESIZE];
    int indice_struct = 0;
    minimal * fichelocalM = calloc(1,sizeof(minimal));
    fichelocalM->nombre_auteur = 0;
    tableaux_fiche tableaux_allfiche;
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.address = NULL;

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
            appendAuteurM(fichelocalM,tmpauteur);
        }else{
            fichelocalM->titre = getanchor("title",ligne);
            if (fichelocalM->titre)
            {
                flagt = 1;
            }
        }

        if (flagt == 1)
        {
            // printM_titre(*fichelocalM);
            // printM_liste_auteur(*fichelocalM);
            appendTabmeaux(&tableaux_allfiche,fichelocalM);
            fichelocalM = calloc(1,sizeof(minimal));;
            exitIfNull(fichelocalM, "new calloc null")
            fichelocalM->nombre_auteur = 0;
        }
        
        indice_struct++;
    }
    printTabmeaux(tableaux_allfiche);

}