#ifndef _DIJKSTRA_
#define _DIJKSTRA_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "fonctions_graphe.h"
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

typedef struct plus_court_chemin_struct
{
    auteur_struct** pcc_tab_ptr_auteur; //tableau de pointeur vers les auteurs ai, du plus court chemin pour arriver à l'auteur ai
    Article_struct** pcc_tab_ptr_Article; //tableau de pointeur vers les Articles Ai, du plus court chemin pour arriver à l'auteur ai (l'auteur d'indice i dans pcc_tab_ptr_auteur)
}plus_court_chemin_struct;



plus_court_chemin_struct* Dijkstra(auteur_struct **graphe, int* size_graphe_ptr, char* nom_auteur_1, char* nom_auteur_2);

void free_Dijkstra(auteur_struct** graphe, int size_graphe, plus_court_chemin_struct *pcc_ptr, int size_pcc_auteur, int size_pcc_Article);

#endif