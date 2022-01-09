#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"
#include<string.h>

typedef enum comparaison_auteur
{
    auteur_1_pas_trouver,
    auteur_1_trouver
}comparaison_auteur;




//renvoie 
Article_struct** Dijkstra(auteur_struct **graphe, int* size_graphe_ptr, char* nom_auteur_1, char* nom_auteur_2)
{
    //recherche de l'auteur_1 dans le graphe

    comparaison_auteur trouver_ou_pas= auteur_1_pas_trouver;
    int indice_auteur=-1;
    for(int i=0; i<*size_graphe_ptr; i++)
    {
        indice_auteur++;
        if(strcomp(nom_auteur_1, graphe[i]->nom_auteur))
        {
            trouver_ou_pas= auteur_1_trouver;
            break
        }
    }

    if(trouver_ou_pas== auteur_1_pas_trouver)
    {
        printf("%s%s%s\n", "l'auteur", nom_auteur_1, "ne figure dans aucun Article");
    }


    //si l'auteur_1 est dans le graphe, on applique Dijkstra pour trouver le plus court chemin entre auteur_1 et auteur_2











}






