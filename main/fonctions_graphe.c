#include <stdio.h>
#include <stdlib.h>
#include "fonctions_graphe.h"
#include "unwrap.h"





typedef enum a_mettre_dans_voisins_ou_pas
{
    a_ne_pas_mettre,
    a_mettre

}a_mettre_dans_voisins_ou_pas;


//on appelera "graphe" le tableau des ptr vers les auteurs contenues dans malistauteur
graphe_struct faire_graphe_ptr_auteur(FILE *file_xml)
{
    
    tab_auteur_struct * malistauteur= gen_tab_auteur_from_xml_et_liaison_article(file_xml);
    
    int size_graphe= malistauteur->nombre_auteur;
    graphe_struct graphe_struct;
    graphe_struct.graphe= malloc(sizeof(auteur_struct*)*size_graphe);
    graphe_struct.size_graphe= size_graphe;

    for(int i=0; i<size_graphe; i++)
    {
        auteur_struct* ai_ptr= &(malistauteur->tab_auteur[i]);
        ai_ptr->size_pcc_auteur= -1;
        ai_ptr->ptr_Article_predecesseur_pcc= malloc(8);
        ai_ptr->ptr_Article_predecesseur_pcc= NULL;
        ai_ptr->ptr_auteur_predecesseur_pcc= malloc(8);
        ai_ptr->ptr_auteur_predecesseur_pcc= NULL;
        graphe_struct.graphe[i]= ai_ptr;
    }

    free(malistauteur);

    return graphe_struct;
}




/*
//test: affichage des voisins des auteurs dans e graphe de ptr d'auteur généré par faire_graphe_ptr_auteur
int main(void)
{

    FILE* graphe_test_Katie= fopen(dbtestKatie "r");

    graphe_struct mon_graphe= faire_graphe_ptr_auteur(graphe_test_Katie);

    fclose(graphe_test_Katie);

  
    for(int k=0; k <mon_graphe.size_graphe; k++)
    {
        printf("%s\n",  mon_graphe.graphe[k]->nom_auteur);
    }
    
    free(mon_graphe.graphe);
    
    
    return 0;
}
*/