#include <stdio.h>
#include <stdlib.h>
// #include "parsing.h"
// #include "list.h"
#include "unwrap.h"

#include <string.h>
#include <pthread.h>
#include <assert.h>

//taille des var stdint.h   


#include "macro.h"

// https://en.wikipedia.org/wiki/Stdarg.h ...) multiple arg
/**
 * @def macro tester si p est null et retourne un message
 * 
 */
#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\


//bench la vitese des comparaison een fonction de la taille des var

// int explore(tab_auteur_struct Auteur_random,int profondeur){
//     if (profondeur > 3)
//     {
//         return 0;
//     }
    
//     shift(profondeur);
//     printf("%s:\n",Auteur_random.tab_auteur->nom_auteur);
//     for (int u = 0; u < Auteur_random.taille; u++)
//     {
//         int nombre_auteur = Auteur_random.tab_auteur->tab_ptr_fiche_min[u]->nombre_auteur;
//         shift(profondeur);
//         printf("\t__%d__:%s\n",nombre_auteur,Auteur_random.tab_auteur->tab_ptr_fiche_min[u]->titre);
//         for (int j = 0; j < nombre_auteur; j++)
//         {
//             shift(profondeur);
//             printf("\t\t%s\n",Auteur_random.tab_auteur->tab_ptr_fiche_min[u]->liste_auteur[j]);
//             // explore(Auteur_random.tab_auteur->tab_ptr_fiche_min[u]->liste_auteur[j],profondeur++);
//         }
//     }
// }

int main()
{

    INFO("exection de tests")

    FILE * DBxml = fopen(serializedb,"r");
    FILE * DBinverse = fopen(serializedbunwrap,"r");

    DEBUG("fichier ouver")

    // FILE * DBxml = fopen(smallserializedb,"r");
    // FILE * DBinverse = fopen(smallserializedbunwrap,"r");


    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")

    DEBUG("check ok")
    unwrap_Graph_struct mongraph =  gen_unwrap_Graph(DBxml,DBinverse);
    tab_Article_struct * matable = mongraph.tab_Article_struct;


    // FILE * DBxml = fopen(originedb,"r");

    // tab_Article_struct * matable = unwrap_ListArticle_from_xml(DBxml);
    // for (int i = 0; i < matable->nombre_Article ; i++)
    // {
    //         printf("%s ==> %d\n",matable->tab_Article[i].nom_Article, matable->tab_Article[i].nombre_auteur);
    //         for (int u = 0; u < matable->tab_Article[i].nombre_auteur; u++)
    //         {
    //             printf("\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->nom_auteur,matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi);
    //             for (int pp = 0; pp < matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi; pp++)
    //             {
    //                 printf("\t\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
    //                 for (int UI = 0; UI < matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
    //                 {
    //                     printf("\t\t\t%s\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur); 
    //                 }
    //             }           
    //         }
    // }

    // pthread_t monthread ;
    // int a = pthread_create(&monthread,NULL,&unwrap_Deserilise,DBinverse);
    // if (a == 0)
    // {
    //     printf("pthread OK\n");
    // }
    // tab_auteur_struct * inverserStruct;

    // // tab_auteur_struct * inverserStruct = unwrap_Deserilise(DBinverse);
    // tableaux_fiche normalStruct = deserialisation(DBxml);

    
    // pthread_join(monthread,&inverserStruct);

    
    // unwrap_Serilise(masterpiece,ouputDB);
    // printList_Auteur(inverserStruct);

    //différence  entre comparer des addresse ou des int ou des strcmp

    // for (int i = 0; i < a.taille; i++)
    // {
    //     for (int d = 0; d < i; d++)
    //     {
            
    //         if (strcmp(a.fiche[d]->titre,a.fiche[i+1]->titre)==0)
    //         {
    //             printf("%f/100%% match\n",((float)(i*100)/(float)(a.taille)));
    //             continue;
    //         }   
    //     }
    // }
    return 0;
}

