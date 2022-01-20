
#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <stdio.h>
#include "../header/unwrap.h"
#include "../header/list.h"
#include <stdlib.h>
#include "../header/fonctions_graphe.h"
#include <string.h>



plus_court_chemin_struct* do_Dijkstra(graphe_struct_Katie graphe_t, char* nom_auteur_1, char* nom_auteur_2);

plus_court_chemin_struct* relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(auteur_struct* ptr_auteur_depart, auteur_struct* ptr_auteur_destination, char* nom_auteur_depart, graphe_struct_Katie graphe_t);

void traitement_auteur_courant_et_mise_a_jour_pile_suivante(auteur_struct* ptr_auteur_courant, int* haut_de_pile_suivante_ptr, int* taille_pcc_ptr, int* pile_suivante);

plus_court_chemin_struct reconstitution_du_pcc_apres_parcours(int* taille_pcc_ptr, auteur_struct* ptr_auteur_destination);


void free_Dijkstra(graphe_struct_Katie graphe_t, plus_court_chemin_struct *pcc_ptr);


#endif