#ifndef SEARCH_H
#define SEARCH_H
#include "../header/unwrap.h"
#include "../header/list.h"

enum{
    TOP_Article,
    TOP_auteur
};

enum{
    searchArticle,
    searchauteur
};

enum{
    typeauteur,
    typeArticle    
};

void scoarboard(const graphe_struct_Konqui * mongraph ,const int getwhat ,const int nbentrer);
void parcour_largeur(const graphe_struct_Konqui graph);

ll_list * stringSearch(const graphe_struct_Konqui * mongraph ,const int getwhat ,const char * inputstr);
void printSearch(ll_list * listchainer,int verbositer);

#endif