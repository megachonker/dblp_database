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

    // FILE * DBxml            = fopen(serializedb,"r");
    // FILE * DBinverse        = fopen(serializedbunwrap,"r");
    // FILE * CacheArticleW    = fopen(serialised_Article,"r");



    FILE * DBxml            = fopen(customxml,"r");
    // FILE * DBinverse        = fopen(serializedbunwrap,"r");
    // FILE * CacheArticleW    = fopen(serialised_Article,"r");
//serialised_Articlecustom


    FILE * custominverarti            = fopen(serialised_Articlecustom,"w");

    FILE * ouputDB = fopen(customserializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "customserializedbunwrap)
    int nbauteur = -1;
    int * pointeurnbauteur = &nbauteur ;
    tab_auteur_struct * malistauteur = unwrap_ListAuteur_from_xml(DBxml,pointeurnbauteur);
    unwrap_Serilise_Index(malistauteur,ouputDB);
    
    fclose(ouputDB);
    //customserializedbunwrap

    FILE * inn = fopen(customserializedbunwrap,"r");
    exitIfNull(inn,"imposible d'ouvrire "customserializedbunwrap)

// ces bon
fseek(DBxml,0,SEEK_SET);
    tab_Article_struct * azerazer = unwrap_ListArticle_from_xml(DBxml);
    serialisation_tab_Article_struct(azerazer,custominverarti);

    fclose(custominverarti);
    FILE * aaaaaaa            = fopen(serialised_Articlecustom,"r");

    // tab_auteur_struct * malistaauteur = unwrap_Deserilise_Index(matablefiche,DBinverse);

    // FILE * CacheArticleW    = fopen(serialised_Article,"r");
    // exitIfNull(CacheArticleW,"INPUT PAS CHEMAIN")

    tab_Article_struct * matable = deserialisation_tab_Article_struct(malistauteur,aaaaaaa);
    INFO("deserialisation terminer")
    exit(0);
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
                    // // printf("\t\t%s ==> %d\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nom_Article,matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur); 
                    // for (int UI = 0; UI < matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->nombre_auteur; UI++)
                    // {
                    //     printf("\t\t\t%s\n",matable->tab_Article[i].tab_ptr_auteur[u]->tab_ptr_Article[pp]->tab_ptr_auteur[UI]->nom_auteur); 
                    // }
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

