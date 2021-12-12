#include <stdio.h>
#include "parsing.h"
#include "list.h"
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
    auteur_pas_trouver,
    auteur_trouver_dans_le_sGc
}comparaison_auteur;

typedef enum stade_de_traitement_de_Gt_pour_l_article_Ai
{
    traitement_Gt_pas_terminer_pour_Ai,
    traitement_Gt_terminer_pour_Ai,
}stade_de_traitement_de_Gt_pour_l_article_Ai;


comparaison_auteur voir_si_il_y_a_un_auteur_de_la_fiche_A_dans_la_liste_sGc(fiche_minimal *A, ll_list *sGc, int *indice_de_l_auteur_trouver_dans_sGc)
{
    ll_node *it_sGc=sGc->first;
    comparaison_auteur trouver_ou_pas=auteur_pas_trouver;
    
    for(int l=0; l<A->nombre_auteur; l++)
    {

        if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
            break;
       
       
       
        for(int r=0; r<sGc->size; r++)
        {
            if(it_sGc->value==A->liste_auteur[l])
            {
                trouver_ou_pas=auteur_trouver_dans_le_sGc;
                *indice_de_l_auteur_trouver_dans_sGc=l;
                break;

            }
  
            it_sGc=it_sGc->next;
        }
    }
    return trouver_ou_pas;
}



void mettre_tous_les_ai_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja(ll_list *sGcn, ll_list *sGcj, ll_list *liste_des_listes_des_sommets_sGc, int idx_sGcn_in_Gt)
{
    ll_node *it_sGcj=sGcj->first;
    ll_node *it_sGcn=sGcn->first;
    
    
    for(int p=0; p<sGcn->size; p++)
    {
        comparaison_auteur *trouver_ou_pas=auteur_pas_trouver;

        for(int m=0; m<sGcj->size; m++)
        {
            if(it_sGcj->value==it_sGcn->value)
            {
                trouver_ou_pas=auteur_trouver_dans_le_sGc; 
                
            }
  
            it_sGcj=it_sGcj->next;
        }

        if(trouver_ou_pas==auteur_pas_trouver) 
            append(sGcj, it_sGcn->value);
        
        it_sGcn=it_sGcn->next;

    }

    ll_remove(liste_des_listes_des_sommets_sGc, idx_sGcn_in_Gt);
}


void fusion_des_sGc_apres_traitement_de_Ai(ll_list *liste_des_ak_de_Ai_mis_dans_sGcj, int idx_j_de_sGcj, ll_list *liste_des_listes_des_sommets_sGc, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    ll_node *it_liste_des_ak_de_Ai_mis_dans_sGcj= liste_des_ak_de_Ai_mis_dans_sGcj->first;
    ll_node *it_Gt=liste_des_listes_des_sommets_sGc->first;
    
    ll_node *sGcj=ll_get_node(liste_des_listes_des_sommets_sGc, idx_j_de_sGcj);
    int idx_du_sGc_dans_Gt_ou_il_y_a_l_auteur=0;
    
    for(int t=0; t<liste_des_ak_de_Ai_mis_dans_sGcj->size; t++) //Pour tout les ak mis dans sGcj
    {
        comparaison_auteur trouver_ou_pas=auteur_pas_trouver;
        
        for(int h=0; h<liste_des_listes_des_sommets_sGc->size; h++)
        {
            if(h==idx_j_de_sGcj)
            {
                it_Gt=it_Gt->next;
                idx_du_sGc_dans_Gt_ou_il_y_a_l_auteur++;
            }

            else
            {
                trouver_ou_pas=voir_si_il_y_a_un_auteur_de_la_liste_L_dans_la_liste_sGc(liste_des_ak_de_Ai_mis_dans_sGcj, it_Gt);    
                if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
                {   
                    mettre_tous_les_ai_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja(it_Gt, sGcj, liste_des_listes_des_sommets_sGc, idx_du_sGc_dans_Gt_ou_il_y_a_l_auteur);
                }
                
                
            }
            it_Gt=it_Gt->next;
            idx_du_sGc_dans_Gt_ou_il_y_a_l_auteur++;

        }
        
        
        it_liste_des_ak_de_Ai_mis_dans_sGcj=it_liste_des_ak_de_Ai_mis_dans_sGcj->next;
    }
    *etat_de_Gt=traitement_Gt_terminer_pour_Ai;
}



void mettre_tous_les_ak_de_Ai_dans_sGcj_sauf_ceux_qui_y_sont_deja(fiche_minimal *Ai, ll_list *sGcj, ll_list *liste_des_ak_de_Ai_mis_dans_sGcj)
{ 
    int *l=-1;
    comparaison_auteur trouver_ou_pas=voir_si_il_y_a_un_auteur_de_la_fiche_A_dans_la_liste_sGc(Ai, sGcj, l);

        if(trouver_ou_pas==auteur_pas_trouver)
        {
            append(sGcj,Ai->liste_auteur[*l]);
            append(liste_des_ak_de_Ai_mis_dans_sGcj,Ai->liste_auteur[*l]);
        }
}






void comparer_l_auteur_k_et_traiter_les_listes_de_sommet_sGc(comparaison_auteur *trouver_ou_pas, char *auteur_k,ll_node *it_auteur_liste_courante, ll_list *liste_des_listes_des_sommets_sGc)
{
    if(!strcmp(auteur_k,it_auteur_liste_courante->value)==0)
    {
        *trouver_ou_pas=auteur_trouver_dans_le_sGc;
    }
    else
    {
        *trouver_ou_pas=auteur_pas_trouver;
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




void voir_si_l_auteur_a_coecrit_article_deja_traité(fiche_minimal *fiche_i, char *auteur_k, ll_list *liste_des_listes_des_sommets_sGc, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    ll_node *liste_courante=liste_des_listes_des_sommets_sGc->first;

    comparaison_auteur *trouver_ou_pas=auteur_pas_trouver;

    for(int j=0; j < liste_des_listes_des_sommets_sGc->size; j++) /* et pour tout ces auteurs on regarde toutes les listes crées*/
        {
            
            parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_fusionner_cetaines_listes_deja_cree(trouver_ou_pas, auteur_k, liste_courante,  liste_des_listes_des_sommets_sGc);
            

            if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
            {
                ll_list *liste_des_ak_de_Ai_mis_dans_sGcj=ll_create();
                mettre_tous_les_ak_de_Ai_dans_sGcj_sauf_ceux_qui_y_sont_deja(fiche_i, liste_courante, liste_des_ak_de_Ai_mis_dans_sGcj);

                fusion_des_sGc_apres_traitement_de_Ai(liste_des_ak_de_Ai_mis_dans_sGcj, j, liste_des_listes_des_sommets_sGc, etat_de_Gt);
                *etat_de_Gt=traitement_Gt_terminer_pour_Ai;

                break;

            }
            
            
            liste_courante=liste_courante->next;
        }
    
    if(trouver_ou_pas==auteur_pas_trouver)
    {
        ll_append(liste_des_listes_des_sommets_sGc, ll_create());
        ll_list *nouvelle_liste=ll_get_node(liste_des_listes_des_sommets_sGc, (liste_des_listes_des_sommets_sGc->size)-1);
        nouvelle_liste->first->value=*auteur_k;
    }
}




void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimal *fiche_i, ll_list * liste_des_listes_des_sommets_sGc, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    for(int k=0; k < fiche_i->nombre_auteur; k++)  /*on regarde les auteurs*/
    {        
        if(etat_de_Gt==traitement_Gt_terminer_pour_Ai)
            break;
        
        voir_si_l_auteur_a_coecrit_article_deja_traité(fiche_i,fiche_i->liste_auteur[k], liste_des_listes_des_sommets_sGc, etat_de_Gt);
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
        stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt=traitement_Gt_pas_terminer_pour_Ai;
        parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(tab_fiche->fiche[i],liste_des_listes_des_sommets_sGc, etat_de_Gt);
    }
    return sommets_sGc0;
}




void free_tout(tout)
{

}









