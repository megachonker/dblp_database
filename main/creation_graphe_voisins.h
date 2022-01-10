#ifndef _CREATION_GRAPHE_VOISINS_
#define _CREATION_GRAPHE_VOISINS_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>

auteur_struct** faire_graphe_avec_unwrap_graphe(int* size_graphe_ptr);

auteur_struct** creation_graphe_avec_voisins(auteur_struct** graphe, int* ptr_size_graphe);

void free_graphe_avec_voisins(auteur_struct** free_graphe_avec_voisins, int* ptr_size_graphe);

#endif