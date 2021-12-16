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


    FILE * inputDB = fopen("DATA/Serialzed1000.data","r");
    FILE * ouputDB = fopen("DATA/SerializedStrucInverse.data","w");

    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    List_Auteur * Amasterpiece = unwrap_from_file(inputDB);
    printList_Auteur(Amasterpiece);
    unwrap_Serilise(Amasterpiece,ouputDB);

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

