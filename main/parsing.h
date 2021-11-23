#ifndef PARSING_H
#define PARSING_H

typedef struct minimal
{
    char * titre;
    char ** liste_auteur;
    int nombre_auteur;
}minimal;

typedef struct tableaux_fiche
{
    minimal ** address;
    int taille;
}tableaux_fiche;


char * getanchor(char * recherche, char * ligne);

void appendAuteurM(char ** liste_auteur,int indice, char * nomsauteur);
void appendTabmeaux(tableaux_fiche * table, minimal * a_ajouter){

void printM_titre(minimal OwO);
void printM_liste_auteur(minimal UwU);

#endif