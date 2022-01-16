#ifndef SEARCH_H
#define SEARCH_H
#include "unwrap.h"
enum{
    TOP_Article,
    TOP_auteur
};

void scoarboard(const unwrap_Graph_struct * mongraph ,const int getwhat ,const int nbentrer);

#endif