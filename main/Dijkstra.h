#include <stdio.h>
#include <unwrap.h>


typedef enum a_deja_mis_dans_voisins_ou_pas
{
    deja_mis,
    pas_mis

}a_deja_mis_dans_voisins_ou_pas;


typedef struct auteurs_graphe
{
    auteurs_graphe **voisins_auteur;

}auteurs_graph;

