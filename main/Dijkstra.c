#include <stdio.h>
#include <unwrap.h>
#include <list.h>
#include <stdlib.h>

ll_list *graphe= ll_create();

FILE * DBxml = fopen("DATA/SerializedStruc.data","r");
FILE * DBinverse = fopen("DATA/SerializedStrucInverse.data","r");

unwrap_Graph_t unwrap_Graph=gen_unwrap_Graph(DBxml, DBinverse);
int size_graphe= unwrap_Graph.tab_auteur_struct->taille;




//creation du grahe: liste des auteurs_graphe (voir Dijkstra.h)
for(int i=0; i<size_graphe; i++)
{
    ll_append(graphe, (auteur_t)(unwrap_Graph.tab_auteur_struct->tab_auteur[i]));
}

//ajout des voisins pour chaque auteur
auteur_courant=graphe->first;

//pour tous les auteurs k du graphe
for(int k=0; k<size_graphe; k++)
{
    int size_tab_A_a_courant=auteur_courant.size;
    a_deja_mis_dans_voisins_ou_pas flag=pas_mis;

    //pour tous les Articles l écrit par l'auteur courant
    for(int l=0; l<size_tab_A_a_courant; l++)
    {
        int nbr_a_dans_A_courant=unwrap_Graph.tab_auteur_struct->tab_auteur[k].tab_ptr_fiche_min[l]->size

        //pour tous les auteurs de l'article courant écrit par l'auteur courant
        for(int m=0; m<)

    }
}





fclose(DBxml);
fclose(DBinverse);