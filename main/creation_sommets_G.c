#include <stdio.h>
#include"parsing.h"
#include"linked-list.h"
#include<stdlib.h>


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


comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(char *auteurk,ll_list *liste_courante, ll_list *liste_des_listes_des_sommets_sGc)
{
    if(*auteurk==liste_courante->value)
    {



       
    }

    else
    {
       
        ll_list sommets_sGc
        append(liste_des_listes_des_sommets_sGc)
       
    }
}





void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(char* auteurk, ll_list *liste_courante,    ll_list *liste_des_listes_des_sommets_sGc)
{
    for(int n=0; n<liste_courante->size) /*et pour toutes ces listes crées, on regarde tout les auteurs contenu dedans*/
    {
        comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(auteurk,   liste_courante, liste_des_listes_des_sommets_sGc);
    }
}




void voir_si_l_auteur_a_coecrit_article_deja_traité(char* auteurk, ll_list *liste_des_listes_des_sommets_sGc)
{
    
    for(int j=0; j<liste_des_listes_des_sommets_sGc->size; j++) /* et pour tout ces auteurs on regarde toutes les listes crées*/
        {
            ll_list *liste_courante=liste_des_listes_des_sommets_sGc->first;
            parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(char* auteurk, liste__courante,  liste_des_listes_des_sommets_sGc);
        
            liste_courante=&(liste_courante->next);

        }
}





void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimal *fiche_i, ll_list liste_des_listes_des_sommets_sGc)
{
    for(int k=0; k<fiche_i->nombre_auteur; k++)  /*on regarde les auteurs*/
    {
        char *auteurk=&(fiche_i->liste_auteur[k]);
        
        voir_si_l_auteur_a_coecrit_article_deja_traité(auteurk, liste_des_listes_des_sommets_sGc);
    }
}






ll_list* creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(tableaux_fiche *tab_fiche) /*création de sommets_G*/
{
    ll_list *liste_des_listes_des_sommets_sGc=ll_create();
    
    ll_list *sommets_sGc0=malloc(sizeof(ll_list));
    ll_append(liste_des_listes_des_sommets_sGc,sommets_sGc0);
    
    for(int i=0; i<tab_fiche->taille; i++) /*pour tout les articles*/
    {
        parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(tab_fiche->fiche[i])
    }
}














int main(void)
{

    return 0;
}