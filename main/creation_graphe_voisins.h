#ifndef _CREATION_GRAPHE_VOISINS_
#define _CREATION_GRAPHE_VOISINS_

#include <stdio.h>
#include <unwrap.h>
#include <list.h>
#include <stdlib.h>
#include <creation_graphe_voisins.h>

auteur_struct** creation_graphe(void);

void free_graphe(auteur_struct** graphe, int* size_graphe);

#endif