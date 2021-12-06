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

// typedef struct Sommet_Auteur
// {
//     char * auteur;
//     ll_list * titre_article;
// }Sommet_Auteur;


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

void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur ){
    for (int i = 0; i < input.taille; i++)
    {
        for (int u = 0; u < input.fiche[i]->nombre_auteur; u++)
        {
            // printf("%s\n",input.fiche[i]->liste_auteur[u]);
            // ll_print_list_as_char(list_chainer_auteur);
            add_entry(list_chainer_auteur,input.fiche[i]->liste_auteur[u],input.fiche[i]->titre);
            // printf("%s\n",input.fiche[i]->liste_auteur[u]);
        }
        float avancement = ((float)(i+1)/(float)input.taille)*100;
        printf("avancement: %f\n",avancement);
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

    print_liste_chainer_Auteur_titre(Liste_chainer);
    // printTabmeaux(mesfiches);

    // #include <string.h>

    // int taill = mesfiches.taille;
    // // taill = 100000;
    // for (int i = 0; i < taill; i++)
    // {
    //     // char listcomp[100];

    //     for (int u = i+1; u < taill; u++)
    //     {
    //         int max = mesfiches.fiche[u]->nombre_auteur;
    //         for (int p = 0; p < max; p++)
    //         {

    //             int nb = mesfiches.fiche[i]->nombre_auteur;
    //             for (int j = 0; j < nb; j++)
    //             {
    //             char * origine = mesfiches.fiche[i]->liste_auteur[j];

    //             // if (mesfiches.fiche[u]->nombre_auteur > -1)
    //             // {
    //                 if (origine!=mesfiches.fiche[u]->liste_auteur[p])
    //                 {
    //                     if (strcmp(origine,mesfiches.fiche[u]->liste_auteur[p])==0)
    //                     {
    //                         // printf("MATCH: %s<=>%s\n",origine,mesfiches.fiche[u]->liste_auteur[p]);
    //                         // free(mesfiches.fiche[u]->liste_auteur[p]);
    //                         mesfiches.fiche[u]->liste_auteur[p] = origine;
    //                     }                         
    //                 }                      
    //             }                
    //         }
            
    //     }
    //         float avancement = ((float)(i+1)/(float)taill)*100;
    //         printf("avancement: %f\n",avancement);  
    // }
    
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

