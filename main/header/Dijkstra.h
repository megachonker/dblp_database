
#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <stdio.h>
#include "../header/unwrap.h"
#include "../header/list.h"
#include <stdlib.h>
#include "../header/fonctions_graphe.h"
#include <string.h>


/**
 * @brief Cette fonction fait un parcours en largeur
 * en mettant à jour la distance des auteur avec l'auteur source
 * 
 * @param graphe_t 
 * @param nom_auteur_1 
 * @param nom_auteur_2 
 * @return plus_court_chemin_struct* 
 */
plus_court_chemin_struct* do_Dijkstra(graphe_struct_Katie graphe_t, char* nom_auteur_1, char* nom_auteur_2);


/**
 * @brief Free ce qui a été alloc dans do_Dijkstra
 * 
 * @param graphe_struct 
 * @param pcc_ptr 
 */
void free_Dijkstra(graphe_struct_Katie graphe_struct, plus_court_chemin_struct *pcc_ptr);


#endif