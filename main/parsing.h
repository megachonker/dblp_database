#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>
#include "list.h"

typedef struct fiche_minimal
{
    char * titre;
    int nombre_auteur;
    char ** liste_auteur;
    //add une uid pour un auteur
}fiche_minimal;

typedef struct tableaux_fiche
{
    fiche_minimal ** fiche;
    int taille;
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