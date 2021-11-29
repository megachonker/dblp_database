#include <stdio.h>
#include "parsing.h"
#include "linked-list.h"
#include <stdlib.h>

#include <string.h>

/* 
   sommets_G: liste des listes de sommet, des sous graphes connexes

   sommets_sGc0: liste des sommets du sous graphe connexe numéro 0
   sommets_sGc1: liste des sommets du sous graphe connexe numéro 1
   .
   .
   .
*/


/*typedef struct auteur
{
    char* nom;

}auteur;



typedef struct liste_d_auteur
{
    auteur *ptr_auteur;

}liste_d_auteur;


typedef struct liste_de_liste_d_auteur
{
    liste_d_auteur liste_sous_graphe_connexe;

}liste_de_liste_d_auteur;*/

/*

comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(char *auteur_k,ll_list *liste_courante, ll_list *liste_des_listes_des_sommets_sGc)
{
    
    if(*auteur_k==liste_courante->value)
    {


*/


comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(char *auteurk,ll_node *liste_courante, ll_list *liste_des_listes_des_sommets_sGc)
{
    if(!strcmp(auteurk,liste_courante->value)==0)
    {
        ll_list sommets_sGc;
        append(liste_des_listes_des_sommets_sGc);
    }
}


void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(char* auteurk, ll_list *liste_courante,    ll_list *liste_des_listes_des_sommets_sGc)
{
    ll_node *it_auteur_liste_courante=&(liste_courante->first);
    
    for(int n=0; n<(liste_courante->size)-1; n++) /*et pour toutes ces listes crées, on regarde tout les auteurs contenu dedans*/
    {
        comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(auteurk,   it_auteur_liste_courante, liste_des_listes_des_sommets_sGc);
        it_auteur_liste_courante=liste_courante->next; /*là y'a possibilité de dépasser la taille de la liste si je me suis loupé*/
    }
}




void voir_si_l_auteur_a_coecrit_article_deja_traité(char * auteurk, ll_list *liste_des_listes_des_sommets_sGc)
{
    ll_node *liste_courante=liste_des_listes_des_sommets_sGc->first;
    parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(auteurk, liste_courante,  liste_des_listes_des_sommets_sGc);

    for(int j=0; j < liste_des_listes_des_sommets_sGc->size; j++) /* et pour tout ces auteurs on regarde toutes les listes crées*/
        {
            liste_courante=liste_courante->next;
            parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(auteurk, liste_courante,  liste_des_listes_des_sommets_sGc);
        }
}





void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimal *fiche_i, ll_list * liste_des_listes_des_sommets_sGc)
{
    for(int k=0; k < fiche_i->nombre_auteur; k++)  /*on regarde les auteurs*/
    {        
        voir_si_l_auteur_a_coecrit_article_deja_traité(fiche_i->liste_auteur[k], liste_des_listes_des_sommets_sGc);
    }
}





//création de sommets_G
ll_list* creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(tableaux_fiche *tab_fiche)
{
    ll_list *liste_des_listes_des_sommets_sGc=ll_create();
    
    ll_list *sommets_sGc0=malloc(sizeof(ll_list));
    liste_des_listes_des_sommets_sGc->size=1;

    ll_append(liste_des_listes_des_sommets_sGc,sommets_sGc0);
    
    for(int i=0; i < tab_fiche->taille; i++) /*pour tout les articles*/
    {
        parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(tab_fiche->fiche[i],liste_des_listes_des_sommets_sGc);
    }
    return sommets_sGc0;
}




void free_tout(tout)
{

}









