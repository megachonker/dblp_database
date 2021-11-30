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

typedef enum comparaison_auteur
{
    auteur_pas_trouvé,
    auteur_trouvé_dans_sGcj
}comparaison_auteur;


void mettre_tous_les_ak_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja(ll_list *sGcn, ll_list *sGcj)
{
    ll_node *it_sGcj=sGcj->first;
    ll_node *it_sGcn=sGcn->first;
    
    for(int p=0; p<sGcn->size; p++)
    {
        comparaison_auteur *comparaison_auteur=auteur_pas_trouvé;

        for(int m=0; m<sGcj->size; m++)
        {
            if(it_sGcj->value==it_sGcn->value)
            {
                comparaison_auteur=auteur_trouvé_dans_sGcj;
            }
  
            it_sGcj=it_sGcj->next;
        }

        if(comparaison_auteur==auteur_pas_trouvé)
            append(sGcj, it_sGcn->value);
        
        it_sGcn=it_sGcn->next;

    }

    ll_free(sGcn);
}






void mettre_tous_les_ak_de_Ai_dans_sGcj_sauf_ceux_qui_y_sont_deja(fiche_minimal *Ai, ll_list *sGcj)
{ 
    
    ll_node *it_sGcj=sGcj->first;
    
    for(int l=0; l<Ai->nombre_auteur; l++)
    {
        comparaison_auteur *comparaison_auteur=auteur_pas_trouvé;

        for(int r=0; r<sGcj->size; r++)
        {
            if(it_sGcj->value==Ai->liste_auteur[l])
            {
                comparaison_auteur=auteur_trouvé_dans_sGcj;
            }
  
            it_sGcj=it_sGcj->next;
        }

        if(comparaison_auteur==auteur_pas_trouvé)
            append(sGcj,Ai->liste_auteur[l]);
    }
}






void comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(comparaison_auteur *comparaison_auteur, char *auteur_k,ll_node *it_auteur_liste_courante, ll_list *liste_des_listes_des_sommets_sGc)
{
    if(!strcmp(auteur_k,it_auteur_liste_courante->value)==0)
    {
        *comparaison_auteur=auteur_trouvé_dans_sGcj;
    }
    else
    {
        *comparaison_auteur=auteur_pas_trouvé;
    }
}


void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(comparaison_auteur *comparaison_auteur,char* auteur_k, ll_list *liste_courante,    ll_list *liste_des_listes_des_sommets_sGc)
{
    ll_node *it_auteur_liste_courante=liste_courante->first;
    
    for(int n=0; n<(liste_courante->size)-1; n++) /*et pour toutes ces listes crées, on regarde tout les auteurs contenu dedans*/
    {
        comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(comparaison_auteur, auteur_k,   it_auteur_liste_courante, liste_des_listes_des_sommets_sGc);
        it_auteur_liste_courante=it_auteur_liste_courante->next; /*là y'a possibilité de dépasser la taille de la liste si je me suis loupé*/
    }
}




void voir_si_l_auteur_a_coecrit_article_deja_traité(fiche_minimal *fiche_i, char *auteur_k, ll_list *liste_des_listes_des_sommets_sGc)
{
    ll_node *liste_courante=liste_des_listes_des_sommets_sGc->first;

    comparaison_auteur *comparaison_auteur=auteur_pas_trouvé;

    for(int j=0; j < liste_des_listes_des_sommets_sGc->size; j++) /* et pour tout ces auteurs on regarde toutes les listes crées*/
        {
            
            parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(comparaison_auteur, auteur_k, liste_courante,  liste_des_listes_des_sommets_sGc);
            

            if(comparaison_auteur==auteur_trouvé_dans_sGcj)
            {
                mettre_tous_les_ak_de_Ai_dans_sGcj_sauf_ceux_qui_y_sont_deja(fiche_i,liste_courante);

            }
            
            
            liste_courante=liste_courante->next;
        }
    
    if(comparaison_auteur==auteur_pas_trouvé)
    {
        ll_append(liste_des_listes_des_sommets_sGc, ll_create());
        ll_list *nouvelle_liste=ll_get_node(liste_des_listes_des_sommets_sGc, (liste_des_listes_des_sommets_sGc->size)-1);
        nouvelle_liste->first->value=*auteur_k;
    }
}




void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimal *fiche_i, ll_list * liste_des_listes_des_sommets_sGc)
{
    for(int k=0; k < fiche_i->nombre_auteur; k++)  /*on regarde les auteurs*/
    {        
        voir_si_l_auteur_a_coecrit_article_deja_traité(fiche_i,fiche_i->liste_auteur[k], liste_des_listes_des_sommets_sGc);
    }
}





//création de sommets_G
ll_list* creation_de_la_liste_des_listes_de_sommet_des_sous_graphes_connexes(tableaux_fiche *tab_fiche)
{
    ll_list *liste_des_listes_des_sommets_sGc=ll_create();
    
    ll_list *sommets_sGc0=malloc(sizeof(ll_list));
    if(sommets_sGc0==NULL)
    {
        return NULL;
    }

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









