#include <stdio.h>
#include "parsing.h"
#include "list.h"
#include <stdlib.h>

#include <string.h>
#include "creation_Gt.h"

comparaison_auteur voir_si_il_y_a_auteur_dans_sGc(char *auteur, ll_list *sGc)
{
    
    comparaison_auteur trouver_ou_pas=auteur_pas_trouver; 
    ll_node *it_sGc=sGc->first;

    for(size_t r=0; r<sGc->size; r++)
    {
        if(it_sGc->value==auteur)
        {
            trouver_ou_pas=auteur_trouver_dans_le_sGc;
            break;

        }
  
        it_sGc=it_sGc->next;
    }
    return trouver_ou_pas;
}




comparaison_auteur voir_si_il_y_a_un_auteur_de_L_dans_sGc(ll_list *L, ll_list *sGc)
{
    ll_node *it_L=L->first;
    ll_node *it_sGc=sGc->first;
    comparaison_auteur trouver_ou_pas=auteur_pas_trouver;
    
    for(size_t m=0; m<L->size; m++)
    {

        if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
            break;
       
       
       
        for(size_t b=0; b<sGc->size; b++)
        {
            if(it_L->value==it_sGc->value)
            {
                trouver_ou_pas=auteur_trouver_dans_le_sGc;
                break;

            }
  
            it_sGc=it_sGc->next;
        }
        it_L=it_L->next;
    }
    return trouver_ou_pas;
}



void mettre_tous_les_ai_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja(ll_list *sGcn, ll_list *sGcj, ll_list *Gt, int idx_sGcn_in_Gt)
{
    ll_node *it_sGcn=sGcn->first;
    
    
    for(size_t p=0; p<sGcn->size; p++)
    {
        comparaison_auteur trouver_ou_pas=voir_si_il_y_a_auteur_dans_sGc(it_sGcn->value, sGcj);

        if(trouver_ou_pas==auteur_pas_trouver) 
            ll_append(sGcj, it_sGcn->value);
        
        it_sGcn=it_sGcn->next;

    }

    ll_remove(Gt, idx_sGcn_in_Gt); // je remove une liste (sGcn) de ma liste Gt. C'est peut être pas compatible avec ll_remove
}


void fusion_des_sGc(ll_list *liste_L_des_a_de_A_mis_dans_sGc, int idx_j_du_sGc_ou_on_a_mis_les_a_de_A, ll_list *Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    ll_node *it_Gt=Gt->first;
    
    ll_node *sGcj=ll_get_node(Gt, idx_j_du_sGc_ou_on_a_mis_les_a_de_A);
    int idx_du_sGc_dans_Gt_ou_il_y_a_auteur_de_la_liste_L=0;
    
    
    
    comparaison_auteur trouver_ou_pas=auteur_pas_trouver;
        
    for(size_t h=0; h<Gt->size; h++)
    {
        if(h==(size_t)idx_j_du_sGc_ou_on_a_mis_les_a_de_A) //on regarde pas sGcj, c'est celui dedans lequel qu'on va mettre les auteurs liés des autres sGc
        {
            it_Gt=it_Gt->next;
            idx_du_sGc_dans_Gt_ou_il_y_a_auteur_de_la_liste_L++;
        }

        else
        {
            trouver_ou_pas=voir_si_il_y_a_un_auteur_de_L_dans_sGc(liste_L_des_a_de_A_mis_dans_sGc, (ll_list*)it_Gt);    
            if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
            {   
                mettre_tous_les_ai_de_sGcn_dans_sGcj_sauf_ceux_qui_y_sont_deja((ll_list*)it_Gt, (ll_list*)sGcj, Gt, idx_du_sGc_dans_Gt_ou_il_y_a_auteur_de_la_liste_L);
            }
                
                
        }
        it_Gt=it_Gt->next;
        idx_du_sGc_dans_Gt_ou_il_y_a_auteur_de_la_liste_L++;

    }
        
    
    *etat_de_Gt=traitement_Gt_terminer_pour_Ai;
}




void mettre_tous_les_a_de_A_dans_sGc_sauf_ceux_qui_y_sont_deja(fiche_minimal *A, ll_list *sGc, ll_list *liste_des_a_de_A_mis_dans_sGc)
{ 
     
    for(int l=0; l<A->nombre_auteur; l++)
    {   
        char *auteur_l=A->liste_auteur[l];   
        comparaison_auteur trouver_ou_pas=voir_si_il_y_a_auteur_dans_sGc(auteur_l, sGc);

        if(trouver_ou_pas==auteur_pas_trouver)
        {
            ll_append(sGc,A->liste_auteur[l]);
            ll_append(liste_des_a_de_A_mis_dans_sGc,A->liste_auteur[l]);
        }
    }
}




void voir_si_l_auteur_a_coecrit_article_deja_traiter(fiche_minimal *A, char *auteur_k, ll_list *Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    ll_node *it_sGc_courant=Gt->first;

    comparaison_auteur trouver_ou_pas=auteur_pas_trouver;

    for(size_t j=0; j < Gt->size; j++) /* et pour tout ces auteurs on regarde toutes les listes crées*/
        {   
            printf("%s\n", "rentrer dans la boucle de test de coecriture d'un nouvel auteur");  
            trouver_ou_pas=voir_si_il_y_a_auteur_dans_sGc(auteur_k, (ll_list*)it_sGc_courant);
            

            if(trouver_ou_pas==auteur_trouver_dans_le_sGc)
            {
                ll_list *liste_des_a_de_A_mis_dans_sGc=ll_create();
                mettre_tous_les_a_de_A_dans_sGc_sauf_ceux_qui_y_sont_deja(A, (ll_list*)it_sGc_courant, liste_des_a_de_A_mis_dans_sGc);

                fusion_des_sGc(liste_des_a_de_A_mis_dans_sGc, j, Gt, etat_de_Gt);
                *etat_de_Gt=traitement_Gt_terminer_pour_Ai;

                break;

            }
            
            
            it_sGc_courant=it_sGc_courant->next;
        }
    
    if(trouver_ou_pas==auteur_pas_trouver)
    {
        printf("%s\n", "etape creation nouveau sGc OK");
        ll_append(Gt, ll_create());
        ll_list *nouvelle_liste=ll_get_node(Gt, (Gt->size)-1);
        *((char*)nouvelle_liste->first->value)=*auteur_k;
    }
}

                                                                                



void parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(fiche_minimal *A, ll_list * Gt, stade_de_traitement_de_Gt_pour_l_article_Ai *etat_de_Gt)
{
    for(int k=0; k < A->nombre_auteur; k++)  /*on regarde les auteurs*/
    {        
        printf("%s\n", "rentrer dans la boucle sur les auteurs d'un nouvel article");
        if(*etat_de_Gt==traitement_Gt_terminer_pour_Ai)
            break;
        
        voir_si_l_auteur_a_coecrit_article_deja_traiter(A,A->liste_auteur[k], Gt, etat_de_Gt);
    }
}





//création de sommets_G
ll_list* creation_Gt(tableaux_fiche *tab_fiche)
{
    ll_list *Gt=ll_create();
    
    ll_list *sommets_sGc0=ll_create();


    ll_append(Gt,sommets_sGc0);
    printf("%s\n", "debut creation_Gt");
    
    for(int i=0; i < tab_fiche->taille; i++) /*pour tout les articles*/
    {
        printf("%s\n", "rentrer dans la boucle sur les Articles du tableau");
        stade_de_traitement_de_Gt_pour_l_article_Ai etat_de_Gt=traitement_Gt_pas_terminer_pour_Ai;
        parcours_liste_des_auteurs_d_un_article_pour_voir_si_il_faut_creer_une_nouvelle_liste(tab_fiche->fiche[i],Gt, &etat_de_Gt);
    }
    //printf("%li\n", Gt->size);
    return Gt;
}





void free_Gt(ll_list *Gt)
{
    ll_node *it_Gt=Gt->first;

    for(size_t p=0; p<Gt->size; p++)
    {
        ll_free(it_Gt->value);
        it_Gt=it_Gt->next;
    }

    ll_free(Gt);
}









