#ifndef FONCTIONS_GRAPHE
#define FONCTIONS_GRAPHE

#include <stdio.h>
#include "../header/unwrap.h"
#include "../header/list.h"
#include <stdlib.h>
#include <string.h>



typedef struct plus_court_chemin_struct
{
    auteur_struct** pcc_tab_ptr_auteur; //tableau de pointeur vers les auteurs ai, du plus court chemin pour arriver à l'auteur ai
    int size_pcc_auteur;
    Article_struct** pcc_tab_ptr_Article; //tableau de pointeur vers les Articles Ai, du plus court chemin pour arriver à l'auteur ai (l'auteur d'indice i dans pcc_tab_ptr_auteur)
    int size_pcc_Article;

}plus_court_chemin_struct;


typedef struct graphe_struct_Katie
{
    auteur_struct ** graphe;
    int size_graphe;

}graphe_struct_Katie;

typedef enum comparaison_auteur
{
    auteur_pas_trouver,
    auteur_trouver
}comparaison_auteur;

typedef enum comparaison_Article
{
    Article_pas_trouver,
    Article_trouver
}comparaison_Article;

typedef struct pcc_struct_verification
{
    char** tab_verif_auteur;
    char** tab_verif_Article;
}pcc_struct_verification;



void verifier_do_Dijkstra(struct plus_court_chemin_struct* pcc);

graphe_struct_Konqui faire_graphe_Konqui(char * DBfiche, char * DBauteur, char * DBArticle);

graphe_struct_Katie faire_graphe_ptr_auteur( graphe_struct_Konqui graphe_Konqui);

void voir_si_un_auteur_est_dans_le_graphe_et_donner_un_Article_ou_il_apparait(graphe_struct_Katie graphe_struct, char* nom_auteur);

void donner_tous_les_Articles_de_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur);

void donner_tous_ceux_qui_ont_travalle_avec_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur);

void print_chemins_auteur_et_Article(plus_court_chemin_struct* pcc);

void print_noms_des_voisins(graphe_struct_Katie graphe_t, char* nom_auteur);


#endif