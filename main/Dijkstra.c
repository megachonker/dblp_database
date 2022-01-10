#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"
#include<string.h>
#include"Dijkstra.h"


auteur_struct** relachemment_arretes_reccursif(auteur_struct* ptr_auteur_courant, auteur_struct* ptr_auteur_destination)
{
    if(ptr_auteur_courant== ptr_auteur_destination)
    {
        return ptr_auteur_destination->plus_court_chemin;
    }
    else
    {
        for(int i=0; i< ptr_auteur_courant->nb_voisins; i++)
        {
            auteur_struct* ptr_voisin_i= ptr_auteur_courant->tab_ptr_voisins[i];

            if(ptr_voisin_i->etiquette== -1)
            {
                ptr_voisin_i->etiquette= 1;
                ptr_voisin_i->plus_court_chemin= ptr_auteur_courant->plus_court_chemin;
                ptr_voisin_i->size_plus_court_chemin++;
                ptr_voisin_i->plus_court_chemin= realloc(ptr_voisin_i->plus_court_chemin, sizeof(auteur_struct*)*ptr_voisin_i->size_plus_court_chemin);
                ptr_voisin_i->plus_court_chemin[ptr_voisin_i->size_plus_court_chemin-1]= ptr_voisin_i;
            }
            else if(ptr_voisin_i->etiquette> ptr_auteur_courant->etiquette+1)
            {
                ptr_voisin_i->etiquette++;
                ptr_voisin_i->plus_court_chemin= ptr_auteur_courant->plus_court_chemin;
                ptr_voisin_i->size_plus_court_chemin++;
                ptr_voisin_i->plus_court_chemin= realloc(ptr_voisin_i->plus_court_chemin, sizeof(auteur_struct*)*ptr_voisin_i->size_plus_court_chemin);
                ptr_voisin_i->plus_court_chemin[ptr_voisin_i->size_plus_court_chemin-1]= ptr_voisin_i;

            }   
        }


        for(int i=0; i< ptr_auteur_courant->nb_voisins; i++)
        {
            relachemment_arretes_reccursif(ptr_auteur_courant->tab_ptr_voisins[i], ptr_auteur_destination);
        }



    }
}





//renvoie le tableau des ptr vers les auteur_struct du chemin de auteur_1 (a1) a auteur_2 (a2)
auteur_struct** Dijkstra(auteur_struct **graphe, int* size_graphe_ptr, char* nom_auteur_1, char* nom_auteur_2)
{
    //verification de la presence de a1 et a2 dans le graphe

    comparaison_auteur_1 trouver_ou_pas_1= auteur_1_pas_trouver;
    comparaison_auteur_2 trouver_ou_pas_2= auteur_2_pas_trouver;
    int indice_auteur= -1;
    auteur_struct* ptr_a2= NULL;
    auteur_struct* ptr_a1= NULL;

    for(int i=0; i<*size_graphe_ptr; i++)
    {
        
        if(strcomp(nom_auteur_1, graphe[i]->nom_auteur))
        {
            trouver_ou_pas_1= auteur_1_trouver;
            ptr_a1= graphe[i];
        }

        if(strcomp(nom_auteur_2, graphe[i]->nom_auteur))
        {
            trouver_ou_pas_2= auteur_2_trouver;
            ptr_a2= graphe[i];
        }

        if(trouver_ou_pas_2== auteur_2_trouver & trouver_ou_pas_1== auteur_1_trouver)
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

    if(trouver_ou_pas_1== auteur_1_pas_trouver || trouver_ou_pas_2== auteur_2_pas_trouver)
        return NULL;


    //si a1 et a2 sont dans le graphe, on applique Dijkstra pour trouver le plus court chemin entre auteur_1 et auteur_2
    //les etiquettes sont deja set up a -1 dans creation_graphe_voisin.c

    //on set up l'etiquette de a1 a 0
    ptr_a1->etiquette= 0;
    ptr_a1->plus_court_chemin= malloc(sizeof(auteur_struct*));
    ptr_a1->plus_court_chemin[0]= ptr_a1;
    ptr_a1->size_plus_court_chemin= 0;

    auteur_struct** plus_court_cheminde_a1_a_a2= relachemment_arretes_reccursif(ptr_a1, ptr_a2);

    return plus_court_cheminde_a1_a_a2;
}



void free_tout(auteur_struct** plus_court_chemin, auteur_struct **graphe, int size_graphe)
{
    for(int i=0; i< size_graphe; i++)
    {
        free(graphe[i]->size_plus_court_chemin);
    }
}


