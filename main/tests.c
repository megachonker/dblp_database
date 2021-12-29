#include <stdio.h>
#include <stdlib.h>
// #include "parsing.h"
// #include "list.h"
#include "unwrap.h"

#include <string.h>

#include <pthread.h>



#include <assert.h>


/**
 * @def macro tester si p est null et retourne un message
 * 
 */
#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\

#define MAXarraySIZE 21143793
Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];



int main()
{

    //tester les free dans parsing
    //ajouter le nombre d'élément dans le serialiser pour les maloc ?
    //dans unwrap sérialiser les titre des hauteur



    
    FILE * DBxml = fopen("DATA/SerializedStruc.data","r");
    FILE * DBinverse = fopen("DATA/SerializedStrucInverse.data","r");
    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")

    tableaux_fiche * matablefiche = deserialisation(DBxml);

    // int sizeHauteurHeuvre = SwapStruct(matablefiche,HauteurHeuvre);
    // sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre);
    // List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    // unwrap_Serilise_Index(malistedauteur,DBinverse);

    List_Auteur * malistesortie = unwrap_Deserilise_Index(matablefiche,DBinverse);
    printList_Auteur(malistesortie);



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

