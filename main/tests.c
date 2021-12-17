#include <stdio.h>
#include <stdlib.h>
// #include "parsing.h"
// #include "list.h"
#include "unwrap.h"

// #include <string.h>

/**
 * @def macro tester si p est null et retourne un message
 * 
 */
#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\



int main()
{
    //lire tout le fichier pour le metrte en maloc est faire un vieux fseek
    // FILE * inputDB = fopen("DATA/Serialzed1000.data","r");
    FILE * inputDBB = fopen("DATA/SerializedStruc.data","r");
    FILE * ouputDB = fopen("DATA/SerializedStrucInverse.data","r");

    // FILE * ouputDB = fopen("DATA/SerializedStrucInverse.data","w");
    exitIfNull(inputDBB,"INPUT PAS CHEMAIN")

    exitIfNull(ouputDB,"INPUT PAS CHEMAIN")
    List_Auteur * masterpiece = unwrap_Deserilise(ouputDB);

    // unwrap_Serilise(masterpiece,ouputDB);
    // printList_Auteur(masterpiece);
    tableaux_fiche a = deserialisation(inputDBB);



    // essayon d'exploirer le graph...



    /**
     * @brief comment booster unwrap_resolve
     * 
     * soit on génèr a chaque foit est on désérialise plus
     * soit on paralelise (gain max 8)
     * trouve une slution pour enlever les FOR FOR
     * on trie est on fait un algo
     * on sérialiser La liste inverser AVEC la liste normal ...
     * 
     */

    /**
     * @brief Construct a new for object
     * 
     * on va demander de résoudre tout les object manuelment 
     * on print tout les auteur contenu
     * 
     * et pour montrer que le cache marche on print tout les auteur précédent de leur object
     * 
     * @param i 
     */
    // for (int i = 0; i < masterpiece->taille; i++)
    // {
    //     unwrap_resolve(masterpiece,&masterpiece->tableaux_Somet_hauteur[i],&a);
    //     for (int u = 0; u < masterpiece->tableaux_Somet_hauteur[i].size; u++)
    //     {
    //         printM(*masterpiece->tableaux_Somet_hauteur[i].heuvre[u]);
    //     }
    //     for (int j = 0; j < i; j++)
    //     {
    //         for (int u = 0; u < masterpiece->tableaux_Somet_hauteur[j].size; u++)
    //         {
    //             printM(*masterpiece->tableaux_Somet_hauteur[j].heuvre[u]);
    //         }
    //     }
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

