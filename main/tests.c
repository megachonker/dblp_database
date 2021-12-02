#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\


//soucis la mémoir
//soucis sommet auteur pointeur sur des auteur tot heuvre 
//soucis check que les tab d'addresse sont nu dans les for if

typedef struct Sommet_Auteur
{
    char * auteur;
    ll_list * titre_article;
}Sommet_Auteur;



void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {
            add_entry(list_chainer_auteur,input.fiche[i]->liste_auteur[u],input.fiche[i]->titre);
        }
    }
    return indice;
}

int main()
{
    // FILE * out = fopen("DATA/SerializedStruc.data","w");
    // exitIfNull(out,"INPUT PAS CHEMAIN")
    // FILE * inputDB = fopen("DATA/dblp.xml","r");
    // exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    // tableaux_fiche mesfiches = parse(inputDB);
    // serialize(mesfiches,out);

    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);
    // printTabmeaux(mesfiches);
    ll_list * Liste_chainer = ll_create();
    convertStruct(mesfiches,Liste_chainer);
    // printHauteur_Heuvre(Liste_chainer);
    // printHauteur_Heuvre(Liste_chainer,sizeHauteurHeuvre );

    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    return 0;
}

