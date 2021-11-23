#ifndef PARSING_H
#define PARSING_H

typedef struct minimal
{
    char * titre;
    char ** liste_auteur;
    int nombre_auteur;
}minimal;


char * getanchor(char * recherche, char * ligne);

void appendAuteurM(char ** liste_auteur,int indice, char * nomsauteur);

void printM_titre(minimal OwO);
void printM_liste_auteur(minimal UwU);

#endif