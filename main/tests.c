#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list-makefile-2/linked-list.h"

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



int convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {
            ll_node *list_chainer_article = ll_search_addr(list_chainer_auteur,input.fiche[i]->liste_auteur[u]);
            if (list_chainer_article)
            {       
                ll_append(list_chainer_article,input.fiche[i]->titre);
            }else{
                Sommet_Auteur new_sommet;
                new_sommet.auteur = input.fiche[i]->liste_auteur[u];
                new_sommet.titre_article = ll_create();
                ll_append(&new_sommet.titre_article,input.fiche[i]->titre);
            }
            
            //structure paire
            // list_chainer[indice].hauteur = input.fiche[i]->liste_auteur[u];


            
            //verrifier que l'auteur selectioner existe dans la liste chainer
            //et ajouter le titre associer a la liste chainer 

            //dans la liste chainer faire des insert comme il faut
            //faire des get auteur

            // ll_list auteur 

            //customiser ll_liste
            //liste chainer pour ajouter mes article a mes uteur

        }
    }
    return indice;
}


int main()
{
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);

    ll_list * Liste_chainer = ll_create();


    int sizeHauteurHeuvre = convertStruct(mesfiches,HauteurHeuvre);
    // printHauteur_Heuvre(HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre );
    printHauteur_Heuvre(HauteurHeuvre,sizeHauteurHeuvre );

    //liste des hauteur trier
    //dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    //a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    //on peut faire une pille de comparaison pour en faire en paralle

    //si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    return 0;
}

