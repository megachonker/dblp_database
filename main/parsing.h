#ifndef PARSING_H
#define PARSING_H

typedef struct minimal
{
    char * titre;
    char ** liste_auteur;
    //add une uid pour un auteur
    int nombre_auteur;
}minimal;

typedef struct tableaux_fiche
{
    minimal ** address;
    int taille;
}tableaux_fiche;

tableaux_fiche  parse(FILE * inputDB);

char * getanchor(char * recherche, char * ligne);


void appendAuteurM(minimal * mafiche,char * nomsauteur);
void appendTabmeaux(tableaux_fiche * table, minimal * a_ajouter);

void printM_titre(minimal OwO);
void printM_liste_auteur(minimal UwU);
void printM(minimal UwO);
void printTabmeaux(tableaux_fiche OwU);


#endif