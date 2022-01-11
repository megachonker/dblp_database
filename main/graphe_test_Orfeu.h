#ifndef _graphe_test_
#define _graphe_test_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"


auteur_struct** creation_graphe_test(Article_struct** tab_Articles_test);

void free_graphe_test(auteur_struct** graphe_test, Article_struct** tab_Articles_test);

#endif