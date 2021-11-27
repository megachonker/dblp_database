#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parsing.h"

#define BALISESIZE 1000

//s->name = strdup(buffer)
//fait un alloc d'une valeur

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\




void printM_titre(fiche_minimal OwO){
    printf("titre:    %s",OwO.titre);
}
void printM_liste_auteur(fiche_minimal UwU){
    printf("auteurs:\n- ");
    for (int i = 0; i < UwU.nombre_auteur; i++)
    {
        printf("%s",UwU.liste_auteur[i]);
        if (i+1<UwU.nombre_auteur)
            printf("- ");
    }
    printf("\n");
}

void printM(fiche_minimal OwU){
    printM_titre(OwU);
    printM_liste_auteur(OwU);   
}

void printTabmeaux(tableaux_fiche UwO){

    for (int i = 0; i < UwO.taille; i++)
    {
        printM(*(UwO.fiche[i]));
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

void appendAuteurM(fiche_minimal * mafiche,char * nomsauteur){
    void * addrListeauteur = realloc(mafiche->liste_auteur,sizeof(fiche_minimal)*(mafiche->nombre_auteur+1));
 
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

void appendTabmeaux(tableaux_fiche * table, fiche_minimal * a_ajouter){

    void * addrListFiche = realloc(table->fiche,sizeof(tableaux_fiche)*(table->taille+1));
 
    if (!addrListFiche)
    {
        fprintf(stderr,"appendTabmeaux: allocation imposible");
        exit(1);
    }else if (table != addrListFiche)
    {
        table->fiche = addrListFiche;
    }
    table->fiche[table->taille] = a_ajouter;
    table->taille++;   
}
//on retourne pas l'original mais une copie ?
tableaux_fiche parse(FILE * inputDB){

    char ligne[BALISESIZE];
    int indice_struct = 0;
    fiche_minimal * fichelocalM = calloc(1,sizeof(fiche_minimal));
    fichelocalM->nombre_auteur = 0;
    tableaux_fiche tableaux_allfiche;// ce n'es pas maloc donc a la sortie de la fonction l'object est détruit ? ? ??
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.fiche = NULL;

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
            fichelocalM = calloc(1,sizeof(fiche_minimal));
            exitIfNull(fichelocalM, "new calloc null")
            fichelocalM->nombre_auteur = 0;
        }
        
        indice_struct++;
    }
    // printTabmeaux(tableaux_allfiche);
    return tableaux_allfiche;
}

//utiliser l'addresse pour pas copier ?
void serialize(const tableaux_fiche mastertab){
    FILE * output = fopen("./DATA/SerializedStruc.data","w");
    exitIfNull(output,"serialize: imposible d'ouvrire le fichier")

    for (int i = 0; i < mastertab.taille; i++)
    {
        fprintf(output,"%s\n",mastertab.fiche[i]->titre);
        fprintf(output,"%i\n",mastertab.fiche[i]->nombre_auteur);
        for (int  u = 0; u < mastertab.fiche[i]->nombre_auteur; u++)
        {
            fprintf(output,"%s\n",mastertab.fiche[i]->liste_auteur[u]);
        }       
    }
}

tableaux_fiche deserialisation(char * path){
    FILE * input = fopen(path,"r");
    exitIfNull(input,"serialize: imposible lire le fichier")

    char ligne[BALISESIZE];
    fiche_minimal * fichelocalM = calloc(1,sizeof(fiche_minimal));
    fichelocalM->nombre_auteur = 0;
    tableaux_fiche tableaux_allfiche;
    tableaux_allfiche.taille = 0;
    tableaux_allfiche.fiche = NULL;


    while (fgets(ligne,BALISESIZE,input))
    {
        if (feof(input))
        {
            exit(3);
        }
        
        fichelocalM->titre = strdup(ligne);
        fgets(ligne,BALISESIZE,input);
        int nbhauteur = atoi(ligne);
        for (int i = 0; i < nbhauteur; i++)
        {
            fgets(ligne,BALISESIZE,input);
            appendAuteurM(fichelocalM,strdup(ligne));
        }
        appendTabmeaux(&tableaux_allfiche,fichelocalM);
        fichelocalM = calloc(1,sizeof(fiche_minimal));
        exitIfNull(fichelocalM, "new calloc null")
        fichelocalM->nombre_auteur = 0;
    }
    return tableaux_allfiche;
}