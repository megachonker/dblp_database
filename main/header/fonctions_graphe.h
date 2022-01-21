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
    int nb_auteurMax;
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


/**
 * @brief Vérifie que les auteurs dans le pcc (plus_court_chemin) renvoyé par do_Dijkstra, sont bien voisins, 
 * et que les Articles dans le pcc sont bien liés aux auteurs qui y sont.
 * 
 * @param pcc 
 */
void verifier_do_Dijkstra(struct plus_court_chemin_struct* pcc);


/**
 * @brief Crée le tableau des auteur_struct et le tableau des Article_struct à partir des fichier en cache généré à partir 
 * du fichier xml.
 * 
 * @param DBfiche 
 * @param DBauteur 
 * @param DBArticle 
 * @return graphe_struct_Konqui 
 */
graphe_struct_Konqui faire_graphe_Konqui(char * DBfiche, char * DBauteur, char * DBArticle);


/**
 * @brief Crée un tableau de pointeur vers les auteur_struct du graphe_Konqui, crée dans la fonction "faire_graphe_Konqui".
 * Ce tableau de pointeur pourra être appelé graphe_Katie
 * 
 * @param graphe_Konqui 
 * @return graphe_struct_Katie 
 */
graphe_struct_Katie faire_graphe_ptr_auteur( graphe_struct_Konqui graphe_Konqui);


void voir_si_un_auteur_est_dans_le_graphe_et_donner_un_Article_ou_il_apparait(graphe_struct_Katie graphe_struct, char* nom_auteur);

void donner_tous_les_Articles_de_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur);

void donner_tous_ceux_qui_ont_travalle_avec_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur);

/**
 * @brief Affiche les auteurs et les Articles du pcc (plus court chemin) retourné par do_Dijkstra
 * 
 * @param pcc 
 */
void print_chemins_auteur_et_Article(plus_court_chemin_struct* pcc);

void print_noms_des_voisins(graphe_struct_Katie graphe_t, char* nom_auteur);
void test_exploration_Article(const tab_Article_struct * mesarticle);
void explorearticle(const Article_struct * monarticle, int profondeur);
#endif