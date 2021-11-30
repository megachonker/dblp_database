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




int convertStruct(tableaux_fiche input, ll_list * list_chainer ){
    int indice = 0;
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {   
            //structure paire
            
            ll_insert(list_chainer,)
            list_chainer[indice].heuvre = input.fiche[i];
            list_chainer[indice].hauteur = input.fiche[i]->liste_auteur[u];
            indice++;


            
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

