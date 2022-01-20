#ifndef SEARCH_H
#define SEARCH_H
#include "../header/unwrap.h"
enum{
    TOP_Article,
    TOP_auteur
};

void scoarboard(const graphe_struct_Konqui * mongraph ,const int getwhat ,const int nbentrer);
void parcour_largeur(const graphe_struct_Konqui graph);
char * find_Article(char * querry, tab_Article_struct * tabarticle);
char * find_auteur(char * querry, tab_auteur_struct * tabauteur);
#endif