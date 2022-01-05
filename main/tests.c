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
// Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

// void shift(int decalage){
// for(int p = 0; p < decalage ; p++)
//     printf("\t");
// }

// int explore(List_Auteur Auteur_random,int profondeur){
//     if (profondeur > 3)
//     {
//         return 0;
//     }
    
//     shift(profondeur);
//     printf("%s:\n",Auteur_random.tableaux_Somet_hauteur->hauteur);
//     for (int u = 0; u < Auteur_random.taille; u++)
//     {
//         int nombre_auteur = Auteur_random.tableaux_Somet_hauteur->heuvre[u]->nombre_auteur;
//         shift(profondeur);
//         printf("\t__%d__:%s\n",nombre_auteur,Auteur_random.tableaux_Somet_hauteur->heuvre[u]->titre);
//         for (int j = 0; j < nombre_auteur; j++)
//         {
//             shift(profondeur);
//             printf("\t\t%s\n",Auteur_random.tableaux_Somet_hauteur->heuvre[u]->liste_auteur[j]);
//             // explore(Auteur_random.tableaux_Somet_hauteur->heuvre[u]->liste_auteur[j],profondeur++);
//         }
//     }
// }

int main()
{


    

    //free de malloc marche pas ....

    //crée une nouvel structure qui 


    // Structure List_Auteur ou les heuvre sont des id des fiche_minimal contenue dans SerializedStrucInverse
    // Structure List_Article ou les article sont des id de SerializedStruct est les heuvre sont 

    //List_Article est générée a partire de List_Auteur on le déplie on trie par noms d'article
    
    //on sérialise les List_Article:
    //  pour le noms d'auteur on stoque l'indexe du noms d'auteur de List_Auteur
    //  pour les article on sotque l'index de la fiche minimal de List_Auteur


    // FILE * DBxml = fopen("DATA/Serialzed1000.data","r");
    // FILE * DBinverse = fopen("DATA/SerializedStrucInverse1000.data","r");

#define originedb           "DATA/dblp.xml"
#define smalloriginedb      "DATA/dblp1sur8.xml"
#define serializedb         "DATA/SerializedStruc.data"
#define smallserializedb    "DATA/Serialzed1000.data"
#define serializedbunwrap   "DATA/SerializedStrucInverse.data"
#define smallserializedbunwrap    "DATA/SerializedStrucInverse1000.data"


    // FILE * DBxml = fopen(serializedb,"r");
    // FILE * DBinverse = fopen(serializedbunwrap,"r");


    FILE * DBxml = fopen(smallserializedb,"r");
    FILE * DBinverse = fopen(smallserializedbunwrap,"r");

    // FILE * DBxml = fopen(serializedb,"r");
    // FILE * DBinverse = fopen(serializedbunwrap,"r");

    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")

    unwrap_Graph mongraphlul = gen_unwrap_Graph(DBxml,DBinverse);
    
    for (size_t i = 0; i < mongraphlul.list_Auteur->taille; i++)
        printf("%d\n",mongraphlul.list_Auteur->tableaux_Somet_hauteur[i].size);
    
    // printList_Article(mongraphlul.list_Article);

    // for (int i = 0; i < mongraphlul.list_Article->nombre_Article ; i++)
    // {
    //     if (mongraphlul.list_Article->pointeur_Article_tableaux[i].nombre_Auteur != 0)
    //     {
    //         printf("OUI %s ==> %d\n",mongraphlul.list_Article->pointeur_Article_tableaux[i].Article, mongraphlul.list_Article->pointeur_Article_tableaux[i].nombre_Auteur);
    //         // for (int u = 0; u < mongraphlul.list_Article->pointeur_Article_tableaux[i].nombre_Auteur; u++)
    //         // {
    //         //     printf("\t%d\n",*mongraphlul.list_Article->pointeur_Article_tableaux[i].pointeur_Auteur_tableaux[u]->hauteur);
    //         // }
            
    //     }else{
    //         printf("NON %s\n",mongraphlul.list_Article->pointeur_Article_tableaux[i].Article);
    //     }
        
    // }
    


    // for (int i = 0; i < mongraphlul.list_Article->nombre_Article; i++)
    // {
    //     Sommet_Article_TableauxD * monArticle = &mongraphlul.list_Article->pointeur_Article_tableaux[i];
    //     printf("%s %d\n",monArticle->Article,monArticle->nombre_Auteur);
    //     for (int u = 0; u < monArticle->nombre_Auteur; u++)
    //     {
    //         Sommet_Auteur_TableauxD * auteurfromarticle  =  monArticle->pointeur_Auteur_tableaux[u];
    //         printf("%s %d\n",auteurfromarticle->hauteur,auteurfromarticle->nbelementmagi);
    //         for (int j = 0; j <  auteurfromarticle->nbelementmagi; j++)
    //         {
    //             Sommet_Article_TableauxD * remonter = auteurfromarticle->pointeur_Article[j];
    //             printf("%s == %s\n",remonter->Article,monArticle->Article);
    //         }
    //     }
    // }
    

    

    // tableaux_fiche * matablefiche = deserialisation(DBxml);
    // List_Auteur * malisteAuteur = unwrap_Deserilise_Index(matablefiche,DBinverse);
    // printList_Auteur(malisteAuteur);    



    // Anna Flagg

    //fonction pour générée des fiche random
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("__%d__:",i);
    //     Sommet_Auteur_TableauxD Auteur_random = malistesortie->tableaux_Somet_hauteur[rand()%malistesortie->taille];
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
    // List_Auteur * inverserStruct;

    // // List_Auteur * inverserStruct = unwrap_Deserilise(DBinverse);
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
    //     unwrap_resolve(inverserStruct,&inverserStruct->tableaux_Somet_hauteur[i],&normalStruct);
    //     for (int u = 0; u < inverserStruct->tableaux_Somet_hauteur[i].size; u++)
    //     {
    //         printM(*inverserStruct->tableaux_Somet_hauteur[i].heuvre[u]);
    //     }
    //     return 0;
    //     // for (int j = 0; j < i; j++)
    //     // {
    //     //     for (int u = 0; u < masterpiece->tableaux_Somet_hauteur[j].size; u++)
    //     //     {
    //     //         printM(*masterpiece->tableaux_Somet_hauteur[j].heuvre[u]);
    //     //     }
    //     // }
    // }

//erreur du a la non existance des fiche ?

    // printList_Auteur(masterpiece);

    // FILE * inputCACHE = fopen("DATA/SerializedStrucInverse.data","r");
    // List_Auteur * masterpiece = unwrap_Deserilise(inputCACHE);
    // printList_Auteur(masterpiece);


    // liste des hauteur trier
    // dans la fonction de trie si 2 foit meme hauteur crée un structure SommetHauteur qui liste les hauteur
    // a chaque comparaison qui match on suprime les occurance le mieux est de décaler 
    // on peut faire une pille de comparaison pour en faire en paralle

    // si  tableaux fiche est déja full trier pour il faudra chercher que les premierre occurance donc gain de tems ?

    // creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(mesfiches);


    // auteur ===> liste cooauteur 
    //     list auteur liste article => liste cooteur

    // les hash avec des chiffreeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeemlkjmlkjmlkjmlkjlmkjlmkjlmklmkjmlkjlkmjlmkjlmkjmlkmlkjmlkjmlkjmlkjmlkjmlkjlmkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkmdv

    return 0;
}

