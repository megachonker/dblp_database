#ifndef CREATION_GT_H
#define CREATION_GT_H

#include "parsing.h"
#include "list.h"


typedef enum comparaison_auteur
{
    auteur_pas_trouver,
    auteur_trouver_dans_le_sGc
}comparaison_auteur;

typedef enum stade_de_traitement_de_Gt_pour_l_article_Ai
{
    traitement_Gt_pas_terminer_pour_Ai,
    traitement_Gt_terminer_pour_Ai,
}stade_de_traitement_de_Gt_pour_l_article_Ai;



/**
 * @brief nouvile pas la doc 
 * 
 * @param A 
 * @param sGc 
 * @param indice_de_l_auteur_trouver_dans_sGc 
 * @return comparaison_auteur 
 */
comparaison_auteur voir_si_il_y_a_un_auteur_de_la_fiche_A_dans_la_liste_sGc(fiche_minimale *A, ll_list *sGc, int *indice_de_l_auteur_trouver_dans_sGc);

void mettre_tous_les_ai_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja(ll_list *sGcn, ll_list *sGcj, ll_list *Gt, int idx_sGcn_in_Gt);

void fusion_des_sGc_apres_traitement_de_Ai(ll_list *liste_des_ak_de_Ai_mis_dans_sGcj, int idx_j_de_sGcj, ll_list *Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt);

void mettre_tous_les_ak_de_Ai_dans_sGcj_sauf_ceux_qui_y_sont_deja(fiche_minimale *Ai, ll_list *sGcj, ll_list *liste_des_ak_de_Ai_mis_dans_sGcj);

void comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(comparaison_auteur *trouver_ou_pas, char *auteur_k,ll_node *it_auteur_liste_courante, ll_list *Gt);

void parcours_liste_des_auteurs_d_un_article(comparaison_auteur *comparaison_auteur,char* auteur_k, ll_list *liste_courante,    ll_list *Gt);

void voir_si_l_auteur_a_coecrit_article_deja_traiter(fiche_minimale *fiche_i, char *auteur_k, ll_list *Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt);

void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimale *fiche_i, ll_list * Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt);

ll_list* creation_Gt(tableaux_fiche *tab_fiche);

#endif