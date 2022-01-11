#ifndef _DIJKSTRA_
#define _DIJKSTRA_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"
#include<string.h>

typedef enum comparaison_auteur_1
{
    auteur_1_pas_trouver,
    auteur_1_trouver
}comparaison_auteur_1;

typedef enum comparaison_auteur_2
{
    auteur_2_pas_trouver,
    auteur_2_trouver
}comparaison_auteur_2;

auteur_struct** relachemment_arretes_reccursif(auteur_struct* ptr_auteur_courant, auteur_struct* ptr_auteur_destination);

auteur_struct** Dijkstra_auteur(auteur_struct **graphe, int* size_graphe_ptr, char* nom_auteur_1, char* nom_auteur_2, int* ptr_size_plus_court_chemin_a1_a2);

void free_Dijkstra(auteur_struct **graphe, int size_graphe);

#endif