#include <stdio.h>
#include <stdlib.h>
// #include "parsing.h"
// #include "list.h"
#include "unwrap.h"

#include <string.h>

#include <pthread.h>



#include <assert.h>

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

// #define MAXarraySIZE 21143793
// Paire_auteur_oeuvre HauteurHeuvre[MAXarraySIZE];

// void shift(int decalage){
// for(int p = 0; p < decalage ; p++)
//     printf("\t");
// }

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


    

    //free de malloc marche pas ....

    //crée une nouvel structure qui 


    // Structure tab_auteur_struct ou les oeuvre sont des id des fiche_minimal contenue dans SerializedStrucInverse
    // Structure tab_Article_struct ou les article sont des id de SerializedStruct est les oeuvre sont 

    //tab_Article_struct est générée a partire de tab_auteur_struct on le déplie on trie par noms d'article
    
    //on sérialise les tab_Article_struct:
    //  pour le noms d'auteur on stoque l'indexe du noms d'auteur de tab_auteur_struct
    //  pour les article on sotque l'index de la fiche minimal de tab_auteur_struct


    // FILE * DBxml = fopen("DATA/Serialzed1000.data","r");
    // FILE * DBinverse = fopen("DATA/SerializedStrucInverse1000.data","r");

#define originedb           "DATA/dblp.xml"
#define smalloriginedb      "DATA/dblp1sur8.xml"
#define serializedb         "DATA/SerializedStruc.data"
#define smallserializedb    "DATA/Serialzed1000.data"
#define serializedbunwrap   "DATA/SerializedStrucInverse.data"
#define smallserializedbunwrap    "DATA/SerializedStrucInverse1000.data"
#define customxml    "DATA/custom.xml"


    FILE * DBxml = fopen(serializedb,"r");
    FILE * DBinverse = fopen(serializedbunwrap,"r");


    // FILE * DBxml = fopen(smallserializedb,"r");
    // FILE * DBinverse = fopen(smallserializedbunwrap,"r");


    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")

    unwrap_Graph_struct mongraph =  gen_unwrap_Graph(DBxml,DBinverse);
    tab_Article_struct * matable = mongraph.tab_Article_struct;


    // FILE * DBxml = fopen(originedb,"r");

    tab_Article_struct * matable = unwrap_ListArticle_from_xml(DBxml);
//Preface. 7280
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
    


    // for (int i = 0; i < mongraphlul.tab_Article_struct->nombre_Article; i++)
    // {
    //     Article_struct * monArticle = &mongraphlul.tab_Article_struct->tab_Article[i];
    //     printf("%s %d\n",monArticle->nom_Article,monArticle->nombre_auteur);
    //     for (int u = 0; u < monArticle->nombre_auteur; u++)
    //     {
    //         auteur_struct * auteurfromarticle  =  monArticle->tab_ptr_auteur[u];
    //         printf("%s %d\n",auteurfromarticle->nom_auteur,auteurfromarticle->nbelementmagi);
    //         for (int j = 0; j <  auteurfromarticle->nbelementmagi; j++)
    //         {
    //             Article_struct * remonter = auteurfromarticle->tab_ptr_Article[j];
    //             printf("%s == %s\n",remonter->nom_Article,monArticle->nom_Article);
    //         }
    //     }
    // }
    

    

    // tableaux_fiche * matablefiche = deserialisation(DBxml);
    // tab_auteur_struct * malisteAuteur = unwrap_Deserilise_Index(matablefiche,DBinverse);
    // printList_Auteur(malisteAuteur);    



    // Anna Flagg

    //fonction pour générée des fiche random
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("__%d__:",i);
    //     auteur_struct Auteur_random = malistesortie->tab_auteur[rand()%malistesortie->taille];
    //     // explore(Auteur_random,0);
    // }
    
    //crée un nouvel index  SerializedStruc qui a des id de SerializedStrucInverse  

    // //lire tout le fichier pour le metrte en maloc est faire un vieux fseek
    // // FILE * inputDB = fopen("DATA/Serialzed1000.data","r");
    // FILE * DBxml = fopen("DATA/SerializedStruc.data","r");
    // FILE * DBinverse = fopen("DATA/SerializedStrucInverse.data","r");
    // exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    // exitIfNull(DBinverse,"INPUT PAS CHEMAIN")

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

    
    // // // unwrap_Serilise(masterpiece,ouputDB);
    // // printList_Auteur(inverserStruct);

    // //différence  entre comparer des addresse ou des int ou des strcmp

    // // for (int i = 0; i < a.taille; i++)
    // // {
    // //     for (int d = 0; d < i; d++)
    // //     {
            
    // //         if (strcmp(a.fiche[d]->titre,a.fiche[i+1]->titre)==0)
    // //         {
    // //             printf("%f/100%% match\n",((float)(i*100)/(float)(a.taille)));
    // //             continue;
    // //         }   
    // //     }
    // // }
    


    // essayon d'exploirer le graph...



    // /**
    //  * @brief comment booster unwrap_resolve
    //  * 
    //  * soit on génèr a chaque foit est on désérialise plus
    //  * soit on paralelise (gain max 8)
    //  * trouve une slution pour enlever les FOR FOR
    //  * on trie est on fait un algo
    //  * on sérialiser La liste inverser AVEC la liste normal ...
    //  * 
    //  */

    // /**
    //  * @brief Construct a new for object
    //  * 
    //  * on va demander de résoudre tout les object manuelment 
    //  * on print tout les auteur contenu
    //  * 
    //  * et pour montrer que le cache marche on print tout les auteur précédent de leur object
    //  * 
    //  * @param i 
    //  */
    // for (int i = 0; i < inverserStruct->taille; i++)
    // {
    //     unwrap_resolve(inverserStruct,&inverserStruct->tab_auteur[i],&normalStruct);
    //     for (int u = 0; u < inverserStruct->tab_auteur[i].size; u++)
    //     {
    //         printM(*inverserStruct->tab_auteur[i].tab_ptr_fiche_min[u]);
    //     }
    //     return 0;
    //     // for (int j = 0; j < i; j++)
    //     // {
    //     //     for (int u = 0; u < masterpiece->tab_auteur[j].size; u++)
    //     //     {
    //     //         printM(*masterpiece->tab_auteur[j].tab_ptr_fiche_min[u]);
    //     //     }
    //     // }
    // }

//erreur du a la non existance des fiche ?

    // printList_Auteur(masterpiece);

    // FILE * inputCACHE = fopen("DATA/SerializedStrucInverse.data","r");
    // tab_auteur_struct * masterpiece = unwrap_Deserilise(inputCACHE);
    // printList_Auteur(masterpiece);


    // liste des nom_auteur trier
    // dans la fonction de trie si 2 foit meme nom_auteur crée un structure SommetHauteur qui liste les nom_auteur
    // a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    // on peut faire une pille de comparaison pour en faire en paralle

    // si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    // auteur ===> liste cooauteur 
    //     list auteur liste article => liste cooteur

    // les hash avec des chiffreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeemlkjmlkjmlkjmlkjlmkjlmkjlmklmkjmlkjlkmjlmkjlmkjmlkmlkjmlkjmlkjmlkjmlkjmlkjlmkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkmdv

    return 0;
}

