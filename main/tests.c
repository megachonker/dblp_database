#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "list.h"
#include "unwrap.h"

#include <string.h>

/**
 * @def macro tester si p est null et retourne un message
 * 
 */
#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\

//PABIEN
#define MAXarraySIZE 21143793
Paire_HauteurHeurvre HauteurHeuvre[MAXarraySIZE];

int main()
{
    //lire tout le fichier pour le metrte en maloc est faire un vieux fseek


    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tableaux_fiche mesfiches = deserialisation(inputDB);


    int sizeHauteurHeuvre = SwapStruct(mesfiches,HauteurHeuvre);
    // printPaire_HauteurHeurvre(HauteurHeuvre);
    sort_tableaux_fiche(HauteurHeuvre,sizeHauteurHeuvre );
    List_Auteur * malistedauteur = gen_List_Auteur(HauteurHeuvre,sizeHauteurHeuvre);
    // printList_Auteur(*malistedauteur);
    // printTabmeaux(mesfiches);



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

