#ifndef SEARCH_H
#define SEARCH_H
#include "unwrap.h"
enum{
    TOP_Article,
    TOP_auteur
};

void scoarboard(const Graph_struct * mongraph ,const int getwhat ,const int nbentrer);
void parcour_largeur(const Graph_struct graph);
char * find_Article(char * querry, tab_Article_struct * tabarticle);
#endif