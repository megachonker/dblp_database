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
#define MAXnameSIZE 2
#define MAXarraySIZE 22000000

#define MaxTitre 0
#define MaxHauteur 0



tableaux_fiche default_loading_Struct(){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    return deserialisation(inputDB);
}

typedef struct hauteurToHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
    int size;//chort  pour grater de la place ? 
    // char heuvre[MAXnameSIZE];
}hauteurToHeurvre;

// typedef struct Sommet_hauteur
// {
//     char * hauteur;
//     fiche_minimal heuvre[MAXarraySIZE];
//     int size;
// }Sommet_hauteur;


hauteurToHeurvre HauteurHeuvre[MAXarraySIZE];
// Sommet_hauteur list_sommet[MaxHauteur];


int comphauteur(const void * a, const void * b){
    //moche
    hauteurToHeurvre * aa = (hauteurToHeurvre*)a;
    hauteurToHeurvre * bb = (hauteurToHeurvre*)b;
    int result = strcmp(aa->hauteur,bb->hauteur);
    // printf("r %i",result);
    // if (aa->hauteur==bb->hauteur)
    // {
    //     return 0;
    // }
    
    
    // if ( result == 0)
    // {
        // optimisation de la mort
    // }
    return result;
}

void printHauteur_Heuvre(hauteurToHeurvre * OwI){
    for (int i = 0; i < OwI->size; i++)
    {
        printf("%s => %s\n",OwI[i].hauteur,OwI[i].heuvre->titre);
    }
}

int convertStruct(tableaux_fiche input, hauteurToHeurvre * arrayout ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            arrayout[indice].heuvre = input.fiche[i];
            arrayout[indice].hauteur = input.fiche[i]->liste_auteur[u];
            // memcpy(arrayout[indice].hauteur,input.fiche[i]->liste_auteur[u],MAXnameSIZE);
            indice++;
        }
    }
    return indice;
}

void sort_tableaux_fiche(hauteurToHeurvre * HauteurHeuvre){
    qsort(HauteurHeuvre,HauteurHeuvre->size,sizeof(hauteurToHeurvre),comphauteur);
}

// void add_titre_to_auteur(Sommet_hauteur * list,char * auteur, char * titre){
//     for (int i = 0; i < list->size; i++)
//     {
//         if(list->hauteur == auteur){
//             list[i];
//         }
//     }
    
// }

// void unique_HtH(hauteurToHeurvre * liste){
//     for (int j = 0; j < liste->size; j++)
//     {
//         int i = 1;
//         if (liste[j].hauteur == liste[j+i].hauteur && i+j < liste->size)
//         {
//             while (liste[j].hauteur == liste[j+i].hauteur && i+j < liste->size)
//             {
//                 add_titre_to_auteur(list_sommet,liste[j].hauteur,liste[i+j].heuvre->titre);
//                 i++;
//             }
//         }        
//     }
    
// }


int main()
{
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);

    HauteurHeuvre->size = convertStruct(mesfiches,HauteurHeuvre);
    // printHauteur_Heuvre(HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre);
    printHauteur_Heuvre(HauteurHeuvre);


    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    return 0;
}
