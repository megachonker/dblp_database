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
#define MAXarraySIZE 21143793

#define MaxTitre 5
#define MaxHauteur 2994451


//soucis la mémoir
//soucis sommet auteur pointeur sur des auteur tot heuvre 
//soucis check que les tab d'addresse sont nu dans les for if


tableaux_fiche default_loading_Struct(){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    return deserialisation(inputDB);
}

typedef struct hauteurToHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
}hauteurToHeurvre;

typedef struct Sommet_hauteur
{
    char * hauteur;
    fiche_minimal * heuvre[MAXarraySIZE];//faire une liste chainer ou des malloc
    // int size;
}Sommet_hauteur;


hauteurToHeurvre HauteurHeuvre[MAXarraySIZE];
Sommet_hauteur list_sommet[MaxHauteur];


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

void printHauteur_Heuvre(hauteurToHeurvre * OwI,int sizeHauteurHeuvre ){
    for (int i = 0; i < sizeHauteurHeuvre ; i++)
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
            indice++;
        }
    }
    return indice;
}

void sort_tableaux_fiche(hauteurToHeurvre * HauteurHeuvre,int sizeHauteurHeuvre ){
    qsort(HauteurHeuvre,sizeHauteurHeuvre ,sizeof(hauteurToHeurvre),comphauteur);
}

void new_titre_to_auteur(Sommet_hauteur* list,const hauteurToHeurvre * in){//on pass le pointeur plus rapide 
    for (int i = 0; i < MaxHauteur; i++)
    {
        //on va j'usqua la fin du tableaux pour trouver un élément nul
        if(!list[i].hauteur){
            list[i].hauteur = in->hauteur;
            list[i].heuvre[0] = in->heuvre;
        }
    }
}

void add_titre_to_auteur(Sommet_hauteur * list,const hauteurToHeurvre HtH){//ces plus logic comme ça mais pluslent ?
    //on enumere tout les somet
    for (int i = 0; i < MaxHauteur; i++)
    {
        //on match quand un sommet hauteur match avec l'auteur qu'on veux add
        if(list[i].hauteur == HtH.hauteur){
            //on detecte la fin du tableaux  est on add
            for (int u = 0; u < MaxTitre; u++)// on cherche a chaque foit sinon on doit stoquer uen variable de taille de tab est ces chian
            {
                //quand ces vide ?
                if (!list[i].heuvre[u])
                {
                    list[i].heuvre[u] = HtH.heuvre;
                }
            }  
        }
    }
    
}

void unique_HtH(const hauteurToHeurvre * liste,int sizeHauteurHeuvre,Sommet_hauteur* list_sommet){
    for (int j = 0; j < sizeHauteurHeuvre; j=j)//on incrémenta pas la
    {
        //quand chaque élément de la liste est un hauteur qu'on va ajouter
        new_titre_to_auteur(list_sommet,&liste[j]);
        int i = 1;
        if (liste[j].hauteur == liste[j+i].hauteur && i+j < sizeHauteurHeuvre)
        {
            while (liste[j].hauteur == liste[j+i].hauteur && i+j < sizeHauteurHeuvre)
            {
                add_titre_to_auteur(list_sommet,liste[i+j]);
                i++;// truc de simon ?
            }
        }
        j+=i;//mais ici
    }
}


int main()
{
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);

    int sizeHauteurHeuvre = convertStruct(mesfiches,HauteurHeuvre);
    // printHauteur_Heuvre(HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre );
    printHauteur_Heuvre(HauteurHeuvre,sizeHauteurHeuvre );
    unique_HtH(HauteurHeuvre,sizeHauteurHeuvre,list_sommet);

    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    return 0;
}
