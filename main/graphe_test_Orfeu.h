#ifndef GRAPHE_TEST_ORFEU_H
#define GRAPHE_TEST_ORFEU_H

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "fonctions_graphe.h"


auteur_struct** creation_graphe_test(Article_struct** tab_Articles_test);

void free_graphe_test(auteur_struct** graphe_test, Article_struct** tab_Articles_test);

#endif