#include <stdio.h>
#include "unwrap.h"
#include <stdlib.h>
#include <string.h>
#include "Dijkstra.h"
#include "fonctions_graphe.h"



plus_court_chemin_struct reconstitution_du_pcc_apres_parcours(auteur_struct* ptr_auteur_destination, auteur_struct* ptr_auteur_depart)
{
    auteur_struct** pcc_tab_ptr_auteur= malloc(sizeof(auteur_struct*)*ptr_auteur_destination->size_pcc_auteur+1);
    exitIfNull(pcc_tab_ptr_auteur,"echec malloc pcc_tab_ptr_auteur"); 
    Article_struct** pcc_tab_ptr_Article= malloc(sizeof(Article_struct*)*ptr_auteur_destination->size_pcc_auteur);
    exitIfNull(pcc_tab_ptr_Article,"echec malloc pcc_tab_ptr_Article"); 

    pcc_tab_ptr_auteur[ptr_auteur_destination->size_pcc_auteur]= ptr_auteur_destination;
    
    auteur_struct* ptr_auteur_it= ptr_auteur_destination;
    int i=1;
    while(ptr_auteur_it!= ptr_auteur_depart)
    {
        pcc_tab_ptr_auteur[ptr_auteur_destination->size_pcc_auteur-i]= ptr_auteur_it->ptr_auteur_predecesseur_pcc;
        pcc_tab_ptr_Article[ptr_auteur_destination->size_pcc_auteur-i-1]= ptr_auteur_it->ptr_Article_predecesseur_pcc;

        ptr_auteur_it= ptr_auteur_it->ptr_auteur_predecesseur_pcc;

        i++;
    }

    plus_court_chemin_struct plus_court_chemin;
    plus_court_chemin.pcc_tab_ptr_auteur= pcc_tab_ptr_auteur;
    plus_court_chemin.size_pcc_auteur= i;
    plus_court_chemin.pcc_tab_ptr_Article= pcc_tab_ptr_Article;
    plus_court_chemin.size_pcc_Article= i-1;
    

    return plus_court_chemin;
}






//"traiter l'auteur courant" siginifie mettre a jour les attributs de tous ses voisins
void traitement_auteur_courant_et_mise_a_jour_pile_suivante(auteur_struct** pile_auteur_a_traiter_etape_courante, auteur_struct** pile_suivante, auteur_struct* ptr_auteur_courant, int* haut_de_pile_courante, int* haut_de_pile_suivante)
{

    for(int l=0; l< ptr_auteur_courant->size; l++)
    {
        Article_struct* ptr_Article_l= ptr_auteur_courant->tab_ptr_Article[l];

        for(int k=0; k< ptr_Article_l->nombre_auteur; k++)
        {
            auteur_struct* ptr_voisin_k= ptr_Article_l->tab_ptr_auteur[k];

            //Si Dijkstra n'est pas encore passé par l'auteur ptr_auteur_courant->tab_voisins[k]
            if(ptr_voisin_k->size_pcc_auteur== -1)
            {
                ptr_voisin_k->size_pcc_auteur= 1;

                //On set up l'auteur_predecesseur de voisin_k
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= malloc(sizeof(auteur_struct*));
                exitIfNull(ptr_voisin_k->ptr_auteur_predecesseur_pcc, "echec malloc ptr_auteur_predecesseur_pcc ");
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= ptr_auteur_courant;

                //On set up l'Article_predecesseur de voisin_k
                ptr_voisin_k->ptr_Article_predecesseur_pcc= malloc(sizeof(Article_struct*));
                exitIfNull(ptr_voisin_k->ptr_Article_predecesseur_pcc, "echec malloc ptr_Article_predecesseur_pcc");
                ptr_voisin_k->ptr_Article_predecesseur_pcc= ptr_Article_l;

                //On ajoute tous les voisins de voisin_k dans la pile_suivante
                for(int j=0; j< ptr_voisin_k->size; j++)
                {
                    for(int p=0; p< ptr_voisin_k->tab_ptr_Article[j]->nombre_auteur; p++)
                    {
                        pile_suivante[*haut_de_pile_suivante]= ptr_voisin_k->tab_ptr_Article[j]->tab_ptr_auteur[p];
                        *haut_de_pile_suivante= *haut_de_pile_suivante+1;
                    }
                }

            }

            //Si Dijkstra est déjà passé par cet auteur mais qu'il a un plus court chemin jusqu'à l'auteur de départ plus court
            else if(ptr_voisin_k->size_pcc_auteur< ptr_auteur_courant->size_pcc_auteur)
            {
                ptr_voisin_k->size_pcc_auteur++;

                //On set up l'auteur_predecesseur de voisin_k
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= malloc(sizeof(auteur_struct*));
                exitIfNull( ptr_voisin_k->ptr_auteur_predecesseur_pcc, "echec malloc ptr_auteur_predecesseur_pcc");
                
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= ptr_auteur_courant;

                //On set up l'Article_predecesseur de voisin_k
                ptr_voisin_k->ptr_Article_predecesseur_pcc= malloc(sizeof(Article_struct*));
                exitIfNull(ptr_voisin_k->ptr_Article_predecesseur_pcc, "echec malloc ptr_Article_predecesseur_pcc");
                ptr_voisin_k->ptr_Article_predecesseur_pcc= ptr_Article_l;

                //On ajoute tous les voisins de voisin_k dans la pile_suivante
                for(int j=0; j< ptr_voisin_k->size; j++)
                {
                    for(int p=0; p< ptr_voisin_k->tab_ptr_Article[j]->nombre_auteur; p++)
                    {
                        pile_suivante[*haut_de_pile_suivante]= ptr_voisin_k->tab_ptr_Article[j]->tab_ptr_auteur[p];
                        *haut_de_pile_suivante= *haut_de_pile_suivante+1;
                    }
                }
    
            }  
        }
    }

    //on vide la pile courante
    for(int j=0; j< *haut_de_pile_courante; j++)
    {
        pile_auteur_a_traiter_etape_courante[j]= NULL;
    }
    *haut_de_pile_courante= 0;   
    
    //on remplie la pile courante avec les auteurs de la pile suivante
    for(int t=0; t< *haut_de_pile_suivante; t++)
    {
        pile_auteur_a_traiter_etape_courante[t]= pile_suivante[t];
        (*haut_de_pile_courante)++;
    }

    //on vide la pile suivante
    for(int i=0; i< *haut_de_pile_suivante; i++)
    {
        pile_suivante[i]= NULL;
    }
    *haut_de_pile_suivante=0;
}



// "traiter l'auteur courant" siginifie mettre a jour les attributs de tous ses voisins
plus_court_chemin_struct* relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(auteur_struct* ptr_auteur_depart, auteur_struct* ptr_auteur_destination, char* nom_auteur_depart)
{
    
    auteur_struct* pile_auteur_a_traiter_etape_courante[1000000];
    auteur_struct* pile_suivante[1000000];
    pile_auteur_a_traiter_etape_courante[0]= ptr_auteur_depart;
    int* haut_de_pile_courante= NULL;
    int* haut_de_pile_suivante= NULL;
    *haut_de_pile_courante=0;
    *haut_de_pile_suivante=0;
    
    
    
    while(pile_auteur_a_traiter_etape_courante[0]!= NULL)
    {
       
        
        for(int i=0; i< *haut_de_pile_courante; i++)
        {
            
            auteur_struct* ptr_auteur_courant= pile_auteur_a_traiter_etape_courante[i];

            if(ptr_auteur_courant== ptr_auteur_destination)
            {
                
                plus_court_chemin_struct* pcc_ptr= malloc(sizeof(plus_court_chemin_struct));
                exitIfNull(pcc_ptr, "echec malloc pcc_ptr");
                *pcc_ptr= reconstitution_du_pcc_apres_parcours(ptr_auteur_destination, ptr_auteur_depart);
                return pcc_ptr;
            }

            traitement_auteur_courant_et_mise_a_jour_pile_suivante(pile_auteur_a_traiter_etape_courante, pile_suivante, ptr_auteur_courant, haut_de_pile_courante, haut_de_pile_suivante);
            
           
        }
    
    }
    printf("Il n'y a pas de chemin entre %s et %s", nom_auteur_depart, ptr_auteur_destination->nom_auteur);
    return NULL;
}





//renvoie le tableau des ptr vers les auteur_struct du chemin de auteur_1 (a1) a auteur_2 (a2)
plus_court_chemin_struct* Dijkstra(graphe_struct graphe_struct, char* nom_auteur_1, char* nom_auteur_2)
{
    //verification de la presence de a1 et a2 dans le graphe

    comparaison_auteur_1 trouver_ou_pas_1= auteur_1_pas_trouver;
    comparaison_auteur_2 trouver_ou_pas_2= auteur_2_pas_trouver;
    auteur_struct* ptr_a2= NULL;
    auteur_struct* ptr_a1= NULL;

    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        
        if(strcmp(nom_auteur_1, graphe_struct.graphe[i]->nom_auteur))
        {
            trouver_ou_pas_1= auteur_1_trouver;
            ptr_a1= graphe_struct.graphe[i];
        }

        if(strcmp(nom_auteur_2, graphe_struct.graphe[i]->nom_auteur))
        {
            trouver_ou_pas_2= auteur_2_trouver;
            ptr_a2= graphe_struct.graphe[i];
        }

        if((trouver_ou_pas_2== auteur_2_trouver) & (trouver_ou_pas_1== auteur_1_trouver))
            break;

    }

    if(trouver_ou_pas_1== auteur_1_pas_trouver)
    {
        printf("%s%s%s\n", "l'auteur", nom_auteur_1, "ne figure dans aucun Article");
    }

    if(trouver_ou_pas_2== auteur_2_pas_trouver)
    {
        printf("%s%s%s\n", "l'auteur", nom_auteur_2, "ne figure dans aucun Article");
    }

    //si l'un des auteurs n'est pas dans la base de donnée, on renvoie un chemin avec que NULL dans le pcc_tab_ptr_auteur
    if(trouver_ou_pas_1== auteur_1_pas_trouver || trouver_ou_pas_2== auteur_2_pas_trouver)
    {
        return NULL;
    }


    //si a1 et a2 sont dans le graphe, on applique Dijkstra pour trouver le plus court chemin entre auteur_1 et auteur_2
    //les  size_plus_court_chemins sont deja set up a -1 dans creation_graphe_voisin.c
    

    plus_court_chemin_struct* plus_court_chemin_de_a1_a_a2= relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(ptr_a1, ptr_a2, nom_auteur_1);
    if(plus_court_chemin_de_a1_a_a2== NULL)
        return NULL;
    
    
    return plus_court_chemin_de_a1_a_a2;
}



void free_Dijkstra(graphe_struct* graphe_struct, plus_court_chemin_struct *pcc_ptr)
{
    if(pcc_ptr!= NULL)
    {
        for(int i=0; i< pcc_ptr->size_pcc_auteur; i++)
        {
            free(pcc_ptr->pcc_tab_ptr_auteur);
        }
        for(int i=0; i< pcc_ptr->size_pcc_Article; i++)
        {
            free(pcc_ptr->pcc_tab_ptr_Article);
        }
        free(pcc_ptr);
    }


    for(int k=0; k< graphe_struct->size_graphe; k++)
    {
        if(graphe_struct->graphe[k]->ptr_Article_predecesseur_pcc!= NULL)
            free(graphe_struct->graphe[k]->ptr_Article_predecesseur_pcc);
        if(graphe_struct->graphe[k]->ptr_auteur_predecesseur_pcc!= NULL)
            free(graphe_struct->graphe[k]->ptr_auteur_predecesseur_pcc);
    }


}

//je test Dijkstra sur mon graphe test en affichant les noms des auteurs du plus court chemin de a0 a a9
int main(void)
{   
    FILE* graphe_test_Katie= fopen(dbtestKatie "r");

    graphe_struct mon_graphe= faire_graphe_ptr_auteur(graphe_test_Katie);

    fclose(graphe_test_Katie);
    
    
    plus_court_chemin_struct* plus_court_chemin=  Dijkstra(mon_graphe,"a4", "a8");

    for(int i=0; i< plus_court_chemin->size_pcc_auteur; i++)
    {
        printf("%s\n", plus_court_chemin->pcc_tab_ptr_auteur[i]->nom_auteur);
    }
    
    free_Dijkstra(&mon_graphe, plus_court_chemin);
    
    

   
    
    return 0;
}