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



//chercher quand on a besoin de fiche minimal
//il est possible de crée le graph sans avoir a charger les fiche minimal ?



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

    FILE * DBxml            = fopen(serializedb,"r");
    FILE * DBinverse        = fopen(serializedbunwrap,"r");
    FILE * CacheArticleW    = fopen(serialised_Article,"r");

    // // DEBUG("fichier ouver")

    // FILE * DBxml = fopen(smallserializedb,"r");
    // FILE * DBinverse = fopen(smallserializedbunwrap,"r");


    // exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    // exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    // exitIfNull(CacheArticleW,"INPUT PAS CHEMAIN")


    // DEBUG("check fichier\nok")
    // INFO("generate graph:")
    // unwrap_Graph_struct mongraph =  gen_unwrap_Graph(DBxml,DBinverse);
    // INFO("genoK")
    // tab_Article_struct * matable = mongraph.tab_Article_struct;


    // INFO("sérialisation Article")    
    // serialisation_tab_Article_struct(matable,CacheArticleW);


    // WARNING("ptitearticlestructok")
    // exit(1);
    // fclose(serializedb);
    // fclose(serializedbunwrap);
    // fclose(serialised_Article);


    // FILE * DBxml = fopen(smallserializedb,"r");
    // FILE * DBinverse = fopen(smallserializedbunwrap,"r");
    // exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    // exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    tableaux_fiche * matablefiche = deserialisation(DBxml);

    tab_auteur_struct * malistaauteur = unwrap_Deserilise_Index(matablefiche,DBinverse);

    // FILE * CacheArticleW    = fopen(serialised_Article,"r");
    // exitIfNull(CacheArticleW,"INPUT PAS CHEMAIN")

    tab_Article_struct * matable = deserialisation_tab_Article_struct(malistaauteur,CacheArticleW);
    INFO("deserialisation terminer")

    // serialised_Article

    //gérée la création

    // FILE * DBxml = fopen(originedb,"r");

    // tab_Article_struct * matable = unwrap_ListArticle_from_xml(DBxml);
    for (int i = 0; i < matable->nombre_Article ; i++)
    {
            printf("%s ==> %d\n",matable->tab_Article[i].nom_Article, matable->tab_Article[i].nombre_auteur);
            for (int u = 0; u < matable->tab_Article[i].nombre_auteur; u++)
            {
                printf("\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->nom_auteur,matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi);
                for (int pp = 0; pp < matable->tab_Article[i].tab_ptr_auteur[u]->nbelementmagi; pp++)
                {
                    printf("\t\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
                    for (int UI = 0; UI < matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
                    {
                        printf("\t\t\t%s\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur); 
                    }
                }           
            }
    }

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

