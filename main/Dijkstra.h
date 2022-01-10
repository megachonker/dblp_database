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


auteur_struct** Dijkstra(auteur_struct **graphe, int* size_graphe_ptr, char* nom_auteur_1, char* nom_auteur_2);