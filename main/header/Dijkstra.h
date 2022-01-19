
#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <stdio.h>
#include "../header/unwrap.h"
#include "../header/list.h"
#include <stdlib.h>
#include "../header/fonctions_graphe.h"
#include <string.h>

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


plus_court_chemin_struct* do_Dijkstra(graphe_struct_Katie graphe_t, char* nom_auteur_1, char* nom_auteur_2);

void free_Dijkstra(graphe_struct_Katie* graphe_t, plus_court_chemin_struct *pcc_ptr);


#endif