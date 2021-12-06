#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\

// typedef struct Sommet_Auteur
// {
//     char * auteur;
//     ll_list * titre_article;
// }Sommet_Auteur;


//soucis la mémoir
//soucis sommet auteur pointeur sur des auteur tot heuvre 
//soucis check que les tab d'addresse sont nu dans les for if


void print_liste_chainer_Auteur_titre(ll_list * list_chainer_auteur){
    int siz = ll_size(list_chainer_auteur);
    for (int i = 0; i < siz; i++)
    {
        Sommet_Auteur * monauteur = ll_get(list_chainer_auteur,i);
        printf("\nAuteur: %s\n",monauteur->auteur);
        ll_list * listart = monauteur->titre_article;
        int sizze = ll_size(listart); 
        for (int j = 1; j < sizze; j++)
        {
            char * mtitre = ll_get(listart,j);
            printf("%s;  \n",mtitre);
        }
    }
}




int main()
{
    //lire tout le fichier pour le metrte en maloc est faire un vieux fseek

    // FILE * out = fopen("DATA/SerializedStruc.data","w");
    // exitIfNull(out,"INPUT PAS CHEMAIN")
    // FILE * inputDB = fopen("DATA/dblp.xml","r");
    // exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    // tableaux_fiche mesfiches = parse(inputDB);
    // serialize(mesfiches,out);



    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    // tableaux_fiche mesfiches = deserialisation(inputDB);
    ll_list * Liste_chainer = deserialisation_Liste(inputDB);



    ll_list_link(Liste_chainer);

    print_liste_chainer_Auteur_titre(Liste_chainer);


    // printTabmeaux(mesfiches);



    
    // printTabmeaux(mesfiches);

    // ll_list * Liste_chainer = ll_create();
    // Sommet_Auteur new_sommet;
    // new_sommet.auteur = mesfiches.fiche[0]->liste_auteur[0];
    // new_sommet.titre_article = ll_create();
    // ll_append(new_sommet.titre_article,mesfiches.fiche[0]->titre);
    // ll_append(Liste_chainer,&new_sommet);

    // convertStruct(mesfiches,Liste_chainer);

    // print_liste_chainer_Auteur_titre(Liste_chainer);

    

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

