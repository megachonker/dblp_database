

#include <stdio.h>
#include "unwrap.h"
#include <stdlib.h>
#include <string.h>
#include "fonctions_graphe.h"
#include "Dijkstra.h"

void print_pile_courante(int* pile_indice, int size, auteur_struct** graphe)
{
    printf("%s\n", "pile courante:");
    for(int k=0; k< size; k++)
    {
        char* nom_auteur= graphe[pile_indice[k]]->nom_auteur;
        printf("%s\n", nom_auteur);
        
    }
    printf("\n");
    printf("%s\n", graphe[pile_indice[0]]->nom_auteur);
    printf("\n\n\n");
}

void print_auteur_indice(auteur_struct** graphe, int size)
{
    for(int k=0; k<size; k++)
    {
        printf("%s:%d\n", graphe[k]->nom_auteur, graphe[k]->indice_dans_le_graphe);
    }
    printf("\n");
}

void print_pile_suivante(int* pile_indice, int size, auteur_struct** graphe)
{
    printf("%s\n", "pile suivante:");
    for(int k=0; k< size; k++)
    {
        char* nom_auteur= graphe[pile_indice[k]]->nom_auteur;
        printf("%s\n", nom_auteur);
        
    }
    printf("\n");
    printf("%s\n", graphe[pile_indice[0]]->nom_auteur);
    printf("\n\n\n");
}


comparaison_auteur trouver_ou_pas_dans_pile(int* haut_de_pile_suivante, int* pile_indice, auteur_struct* ptr_auteur, auteur_struct** graphe)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    for(int k=0; k< *haut_de_pile_suivante; k++)
    {
        if(graphe[pile_indice[k]]==ptr_auteur)
            trouver_ou_pas= auteur_trouver;
    }

    return trouver_ou_pas;
}

plus_court_chemin_struct reconstitution_du_pcc_apres_parcours(int* taille_pcc_ptr, auteur_struct* ptr_auteur_destination)
{
    //printf("%d\n", *taille_pcc_ptr );
    plus_court_chemin_struct plus_court_chemin;
    plus_court_chemin.size_pcc_auteur= (*taille_pcc_ptr);
    plus_court_chemin.size_pcc_Article= (*taille_pcc_ptr)-1;
    //printf("%d\n", *taille_pcc_ptr);

    plus_court_chemin.pcc_tab_ptr_auteur= malloc(sizeof(auteur_struct*)**taille_pcc_ptr);
    //printf("p: %p\n", plus_court_chemin.pcc_tab_ptr_auteur);

    exitIfNull(plus_court_chemin.pcc_tab_ptr_auteur,"echec malloc pcc_tab_ptr_auteur"); 

    
    plus_court_chemin.pcc_tab_ptr_Article= malloc(sizeof(Article_struct*)*((*taille_pcc_ptr)-1));
    exitIfNull(plus_court_chemin.pcc_tab_ptr_Article,"echec malloc pcc_tab_ptr_Article"); 
    //printf("%d\n", *taille_pcc_ptr);


    //on remplie le pcc (plus court chemin) avec les auteurs et Articles emprunté
    plus_court_chemin.pcc_tab_ptr_auteur[(*taille_pcc_ptr)-1]= ptr_auteur_destination;
    //printf("auteur_dest: %s\n", ptr_auteur_destination->nom_auteur);
    
    auteur_struct* ptr_auteur_it= ptr_auteur_destination;
    for(int t=(*taille_pcc_ptr)-2; t>=0; t--)
    {
        plus_court_chemin.pcc_tab_ptr_auteur[t]= ptr_auteur_it->ptr_auteur_predecesseur_pcc;
        plus_court_chemin.pcc_tab_ptr_Article[t]= ptr_auteur_it->ptr_Article_predecesseur_pcc;

        ptr_auteur_it= ptr_auteur_it->ptr_auteur_predecesseur_pcc;
        
    }
    //print_pcc_auteur(plus_court_chemin);
    
    //printf("%d\n", *taille_pcc_ptr);
    

 
    

    return plus_court_chemin;
}






//"traiter l'auteur courant" siginifie mettre a jour la size_pcc_auteur de tous ses voisins
void traitement_auteur_courant_et_mise_a_jour_pile_suivante(int* pile_suivante, auteur_struct* ptr_auteur_courant, int* haut_de_pile_suivante_ptr, int* taille_pcc_ptr)
{
    //printf("%s::::: \n", ptr_auteur_courant->nom_auteur);
    for(int l=0; l< ptr_auteur_courant->size; l++)
    {
        
        Article_struct* ptr_Article_l= ptr_auteur_courant->tab_ptr_Article[l];
        //printf("%s: \n", ptr_Article_l->nom_Article);

        for(int k=0; k< ptr_Article_l->nombre_auteur; k++)
        {
            auteur_struct* ptr_voisin_k= ptr_Article_l->tab_ptr_auteur[k];
            //printf("indice_supposé:%d\n", ptr_voisin_k->indice_dans_le_graphe);
            //printf("indice de a9:%d\n", graphe_t.graphe[9]->indice_dans_le_graphe);
            //print_auteur_indice(graphe_t.graphe, graphe_t.size_graphe);
           


            //Si Dijkstra n'est pas encore passé par l'auteur ptr_auteur_courant->tab_voisins[k]
            if(ptr_voisin_k->size_pcc_auteur== -1 ) 
            {
                //printf("%s \n\n", ptr_voisin_k->nom_auteur);
                //On ajoute tous les indices des voisins de auteur_courant dans la pile_suivante, sauf ceux qui y sont deja, et sauf ceux qui étaient dans la plile_courante, et sauf ceux qui y sont deja
            
                //printf("%s\n", "rentrer dans le if de remplissage de pile_suivante");
                //printf("haut_de_pile_suivante:%d\n", *haut_de_pile_suivante_ptr);
                pile_suivante[*haut_de_pile_suivante_ptr]= ptr_voisin_k->indice_dans_le_graphe;
                //printf("indice_auteur_a_mettre_dans_suivante:%d\n", ptr_voisin_k->indice_dans_le_graphe);
                *haut_de_pile_suivante_ptr= *haut_de_pile_suivante_ptr+1;
            
                
                //print_pile_courante(pile_auteur_a_traiter_etape_courante, *haut_de_pile_courante_ptr, graphe);
                //print_pile_suivante(pile_suivante, *haut_de_pile_suivante_ptr, graphe);
                //printf("LA\n");
                //on met à jour la distance à l'auteur de depart, de voisin_k 
                ptr_voisin_k->size_pcc_auteur= *taille_pcc_ptr;
                //printf("taille_pcc_ptr:%d\n", *taille_pcc_ptr);
                //printf("distance pcc %s: %d\n", ptr_voisin_k->nom_auteur, ptr_voisin_k->size_pcc_auteur);
                //On set up l'auteur_predecesseur de voisin_k
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= malloc(sizeof(auteur_struct*));
                exitIfNull(ptr_voisin_k->ptr_auteur_predecesseur_pcc, "echec malloc ptr_auteur_predecesseur_pcc ");
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= ptr_auteur_courant;
                //On set up l'Article_predecesseur de voisin_k
                ptr_voisin_k->ptr_Article_predecesseur_pcc= malloc(sizeof(Article_struct*));
                exitIfNull(ptr_voisin_k->ptr_Article_predecesseur_pcc, "echec malloc ptr_Article_predecesseur_pcc");
                ptr_voisin_k->ptr_Article_predecesseur_pcc= ptr_Article_l;
                
                //print_pile_suivante(pile_suivante, *haut_de_pile_suivante_ptr, graphe_struct);
                
                
            }
        }
        
    }
    
}



// "traiter l'auteur courant" siginifie mettre a jour les attributs de tous ses voisins
plus_court_chemin_struct* relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(auteur_struct* ptr_auteur_depart, auteur_struct* ptr_auteur_destination, char* nom_auteur_depart, graphe_struct graphe_t)
{
    //les piles, sont des tableau d'indice d'auteur, indice dans le graphe
    int* pile_auteur_a_traiter_etape_courante= malloc(sizeof(int)*1000000);
    exitIfNull(pile_auteur_a_traiter_etape_courante, "echec malloc pile_auteur_a_traiter_etape_courante");
    int* pile_suivante= malloc(sizeof(int)*1000000);
    exitIfNull(pile_suivante, "echec malloc pile_suivante");

    pile_auteur_a_traiter_etape_courante[0]= ptr_auteur_depart->indice_dans_le_graphe;
    int haut_de_pile_courante=1;
    int haut_de_pile_suivante=0;
    int* haut_de_pile_courante_ptr= &haut_de_pile_courante;
    int* haut_de_pile_suivante_ptr= &haut_de_pile_suivante;

    ptr_auteur_depart->size_pcc_auteur= 0;
    
    
    
    int taille_pcc=1; //=profondeur du parcour en largeur (à la fin, =taille du plus court chemin)
    int* taille_pcc_ptr= &taille_pcc;
    while(pile_auteur_a_traiter_etape_courante[0]!= -1)
    {
        
        //printf("%s\n", "rentrer dans le while");
        //printf("%d\n", *taille_pcc_ptr);
        for(int i=0; i< *haut_de_pile_courante_ptr; i++)
        {
            //printf("%s\n", "rentrer dans le for");
            auteur_struct* ptr_auteur_courant= graphe_t.graphe[pile_auteur_a_traiter_etape_courante[i]];
            //printf("%s\n", ptr_auteur_courant->nom_auteur);
            //printf("%s\n", ptr_auteur_destination->nom_auteur);


            if(ptr_auteur_courant== ptr_auteur_destination)
            {
                //printf("%s\n", "rentrer dans le if de fin");
                free(pile_auteur_a_traiter_etape_courante);
                free(pile_suivante);


                //printf("à la base: %d\n", *taille_pcc_ptr);
                plus_court_chemin_struct* pcc_ptr= malloc(sizeof(plus_court_chemin_struct));
                exitIfNull(pcc_ptr, "echec malloc pcc_ptr");
                *pcc_ptr= reconstitution_du_pcc_apres_parcours(taille_pcc_ptr, ptr_auteur_destination);
                return pcc_ptr;
            }

            //printf("%s\n", "on va jusqu'à, juste avent le traitement");
            traitement_auteur_courant_et_mise_a_jour_pile_suivante(pile_suivante, ptr_auteur_courant, haut_de_pile_suivante_ptr, taille_pcc_ptr);
            
           
        }
        

        //on vide la pile courante
        //une pile vide est constituée de -1 sur les cases occupées

        for(int j=0; j< *haut_de_pile_courante_ptr; j++)
        {
            pile_auteur_a_traiter_etape_courante[j]= -1;
        }
        *haut_de_pile_courante_ptr= 0;   

        //si la pile suivante est vide on met à -1 le premier element de la pile courante
        if(pile_suivante[0]== -1)
        { 
            //printf("%s\n", "rentrer dans le if d'avant fin");
            pile_auteur_a_traiter_etape_courante[0]= -1;
        }
        else                           //sinon, on remplie la pile courante avec les indice d'auteur de la pile suivante 
        {
            for(int t=0; t< *haut_de_pile_suivante_ptr; t++)
            {
                pile_auteur_a_traiter_etape_courante[t]= pile_suivante[t];
                (*haut_de_pile_courante_ptr)++;
            }
        }
        //print_pile_courante(pile_auteur_a_traiter_etape_courante, *haut_de_pile_courante_ptr, graphe);
        //print_pile_suivante(pile_suivante, *haut_de_pile_suivante_ptr, graphe);   

        //on vide la pile suivante
        for(int i=0; i< *haut_de_pile_suivante_ptr; i++)
        {
            pile_suivante[i]= -1;
        }
        //print_pile_courante(pile_auteur_a_traiter_etape_courante, *haut_de_pile_courante_ptr, graphe);
        *haut_de_pile_suivante_ptr=0;
        (*taille_pcc_ptr)++;
            
        
       
            

    
    }
    free(pile_auteur_a_traiter_etape_courante);
    free(pile_suivante);
    printf("Il n'y a pas de chemin entre %s et %s\n", nom_auteur_depart, ptr_auteur_destination->nom_auteur);
    return NULL;
}





//renvoie le tableau des ptr vers les auteur_struct du chemin de auteur_1 (a1) a auteur_2 (a2)
plus_court_chemin_struct* do_Dijkstra(graphe_struct graphe_t, char* nom_auteur_1, char* nom_auteur_2)
{
    //verification de la presence de a1 et a2 dans le graphe

    comparaison_auteur_1 trouver_ou_pas_1= auteur_1_pas_trouver;
    comparaison_auteur_2 trouver_ou_pas_2= auteur_2_pas_trouver;
    auteur_struct* ptr_a2= NULL;
    auteur_struct* ptr_a1= NULL;


    for(int i=0; i<graphe_t.size_graphe; i++)
    {
        graphe_t.graphe[i]->indice_dans_le_graphe= i;
        //printf("ce que je met dans les indice d'auteur-> %s:%d\n", graphe_t.graphe[i]->nom_auteur, i);

        if(strcmp(nom_auteur_1, graphe_t.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas_1= auteur_1_trouver;
            ptr_a1= graphe_t.graphe[i];
            //printf("%s\n", ptr_a1->nom_auteur);
        }

        if(strcmp(nom_auteur_2, graphe_t.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas_2= auteur_2_trouver;
            ptr_a2= graphe_t.graphe[i];
            //printf("%s\n", ptr_a2->nom_auteur);
        }
    }

    if(trouver_ou_pas_1== auteur_1_pas_trouver)
    {
        printf("%s %s %s\n", "l'auteur", nom_auteur_1, "ne figure dans aucun Article");
    }

    if(trouver_ou_pas_2== auteur_2_pas_trouver)
    {
        printf("%s %s %s\n", "l'auteur", nom_auteur_2, "ne figure dans aucun Article");
    }

    //si l'un des auteurs n'est pas dans la base de donnée, on renvoie un chemin avec que NULL dans le pcc_tab_ptr_auteur
    if(trouver_ou_pas_1== auteur_1_pas_trouver || trouver_ou_pas_2== auteur_2_pas_trouver)
    {
        return NULL;
    }


    //si a1 et a2 sont dans le graphe, on applique Dijkstra pour trouver le plus court chemin entre auteur_1 et auteur_2
    //les  size_plus_court_chemins sont deja set up a -1 dans creation_graphe_voisin.c
    
    //print_auteur_indice(graphe_t.graphe, graphe_t.size_graphe);
    plus_court_chemin_struct* plus_court_chemin_de_a1_a_a2= relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(ptr_a1, ptr_a2, nom_auteur_1, graphe_t);
    
    //cas ou j'ai tout parcouru
    if(plus_court_chemin_de_a1_a_a2== NULL)
        return NULL;
    
    
    return plus_court_chemin_de_a1_a_a2;
}



void free_Dijkstra(graphe_struct* graphe_struct, plus_court_chemin_struct *pcc_ptr)
{
    
    if(pcc_ptr!= NULL)
    {  
        free(pcc_ptr->pcc_tab_ptr_auteur);
        free(pcc_ptr->pcc_tab_ptr_Article);
        free(pcc_ptr);
    }


    for(int k=0; k< graphe_struct->size_graphe; k++)
    {
        free(graphe_struct->graphe[k]->ptr_Article_predecesseur_pcc);
        free(graphe_struct->graphe[k]->ptr_auteur_predecesseur_pcc);
    }

    free(graphe_struct->graphe);



}



void print_chemins_auteur_et_Artice(plus_court_chemin_struct* pcc)
{
    
    graphe_struct mon_graphe= faire_graphe_ptr_auteur();
    
    plus_court_chemin_struct* plus_court_chemin= do_Dijkstra( mon_graphe," algorithm.", "Azzedine Boukerche");

    if(plus_court_chemin!=NULL)
    {
        printf("chemin auteur: \n");
        for(int i=0; i< pcc->size_pcc_auteur; i++)
        {
            printf("%s\n", pcc->pcc_tab_ptr_auteur[i]->nom_auteur);
        }
        printf("\n\n chemin Article\n");
        for(int i=0; i< pcc->size_pcc_Article; i++)
        {
            printf("%s\n", pcc->pcc_tab_ptr_Article[i]->nom_Article);
        }
    }
}

//je test Dijkstra sur mon graphe test en affichant les noms des auteurs du plus court chemin de a0 a a9
int main(void)
{   
    FILE* graphe_test_Katie= fopen("DATA", "r");

    graphe_struct mon_graphe= faire_graphe_ptr_auteur(graphe_test_Katie);

    fclose(graphe_test_Katie);
    
    //char* nom_auteur_depart= mon_graphe.graphe[1344]->nom_auteur;
    //printf("nom auteur_depart: %s\n", nom_auteur_depart);
    //char* nom_auteur_destination= mon_graphe.graphe[8888]->nom_auteur;
    //printf("nom auteur_destination: %s\n", nom_auteur_destination);
    
    char* nom_auteur_depart= mon_graphe.graphe[1234]->nom_auteur;
    char* nom_auteur_destination= mon_graphe.graphe[1234]->nom_auteur;

    plus_court_chemin_struct* plus_court_chemin=  do_Dijkstra(mon_graphe, nom_auteur_depart, nom_auteur_destination);

    
    if(plus_court_chemin!= NULL)
    {
        print_chemins_auteur_et_Artice(plus_court_chemin);

        verifier_do_Dijkstra(plus_court_chemin);
    }

   //free_Dijkstra(&mon_graphe, plus_court_chemin);
    
    

   
    
    return 0;
}