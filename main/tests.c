#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "creation_sommets_G.h"


#include <string.h>

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\


//2go de tableaux ?
#define MAXnameSIZE 20
#define MAXarraySIZE 22000000

tableaux_fiche default_loading_Struct(){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    return deserialisation(inputDB);
}

typedef struct hauteurToHeurvre
{
    char hauteur[MAXnameSIZE];
    char heuvre[MAXnameSIZE];
}hauteurToHeurvre;

int comphauteur(const void * a, const void * b){
    //moche
    hauteurToHeurvre * aa = (hauteurToHeurvre*)a;
    hauteurToHeurvre * bb = (hauteurToHeurvre*)b;
    int result = strcmp(aa->hauteur,bb->hauteur);
    // if ( result == 0)
    // {
        // optimisation de la mort
    // }
    return result;
}

void printHauteur_Heuvre(hauteurToHeurvre * OwI,int maxsize){
    for (int i = 0; i < maxsize; i++)
    {
        printf("%s => %s\n",OwI[i].hauteur,OwI[i].heuvre);
    }
}

int convertStruct(tableaux_fiche input, hauteurToHeurvre * arrayout ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            indice++;
            strcpy(arrayout[indice].heuvre,input.fiche[i]->titre);
            strcpy(arrayout[indice].hauteur,input.fiche[i]->liste_auteur[u]);
        }
    }
    return indice;
}

void sort_tableaux_fiche(hauteurToHeurvre * HauteurHeuvre,int maxsize){
    qsort(HauteurHeuvre,maxsize,sizeof(hauteurToHeurvre),comphauteur);
}


hauteurToHeurvre HauteurHeuvre[MAXarraySIZE];


int main()
{
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);

    int maxsize = convertStruct(mesfiches,HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,maxsize);
    printHauteur_Heuvre(HauteurHeuvre,maxsize);

    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    return 0;
}
