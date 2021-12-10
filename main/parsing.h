#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>
#include "list.h"

/**
 * @brief Titre && liste des auteur
 * 
 */
typedef struct fiche_minimal
{
    char * titre;           ///< titre de l'heuvre / article
    int nombre_auteur;      ///< nombre d'auteur
    char ** liste_auteur;   ///< liste de liste de caractere des noms d'auteur
    //add une uid pour un auteur
}fiche_minimal;

/**
 * @brief Contien toute les fiche_minimal
 * @struct tableaux_fiche
 */
typedef struct tableaux_fiche
{
    fiche_minimal ** fiche; ///< tableaux des fiche_minimal utiliser
    int taille;             ///<taille tableaux
}tableaux_fiche;

tableaux_fiche parse(FILE * inputDB);

char * getanchor(char * recherche, char * ligne);


void appendAuteurM(fiche_minimal * mafiche,char * nomsauteur);
void appendTabmeaux(tableaux_fiche * table, fiche_minimal * a_ajouter);

void printM_titre(fiche_minimal OwO);
void printM_liste_auteur(fiche_minimal UwU);
void printM(fiche_minimal UwO);
void printTabmeaux(tableaux_fiche OwU);

void serialize(tableaux_fiche mastertab, FILE * outfichier);
tableaux_fiche deserialisation(FILE * input);
ll_list * deserialisation_Liste(FILE * input);



#endif