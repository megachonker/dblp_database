#include <stdio.h>
#include <stdlib.h>
#include "unwrap.h"
#include "fonctions_graphe.h"




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


//Je vérifie que les auteurs du chemin sont bien voisins 2 à 2 dans l'ordre du chemin
//et que les Articles du pcc sont bien cohérent avec le pcc auteur
void verifier_do_Dijkstra(plus_court_chemin_struct* pcc)
{
    pcc_struct_verification pcc_verif;
    pcc_verif.tab_verif_auteur= malloc(sizeof(char*)*pcc->size_pcc_auteur);
    pcc_verif.tab_verif_Article= malloc(sizeof(char*)*pcc->size_pcc_Article);
    
   
    pcc_verif.tab_verif_auteur[0]= "OK";

    for(int k=0; k< pcc->size_pcc_auteur-1; k++) //pour tout les auteurs ak du pcc
    {

        comparaison_auteur trouver_ou_pas_1= auteur_pas_trouver;
        comparaison_Article trouver_ou_pas_2= Article_pas_trouver;

        auteur_struct* ak_ptr= pcc->pcc_tab_ptr_auteur[k];
        auteur_struct* prochain_ak_ptr= pcc->pcc_tab_ptr_auteur[k+1];

        
        for(int l=0; l< ak_ptr->size; l++) //pour tout les Articles Al de ak
        {
            
            Article_struct* Al_ptr= ak_ptr->tab_ptr_Article[l];

            if(Al_ptr== pcc->pcc_tab_ptr_Article[k])
            {
                trouver_ou_pas_2= Article_trouver;
                pcc_verif.tab_verif_Article[k]= "OK";
            }
                
            for(int v=0; v< Al_ptr->nombre_auteur; v++)
            {
                auteur_struct* voisin_de_ak_ptr= Al_ptr->tab_ptr_auteur[v];
                if(voisin_de_ak_ptr== prochain_ak_ptr)
                {
                    trouver_ou_pas_1= auteur_trouver;
                    pcc_verif.tab_verif_auteur[k+1]= "OK";
                }


            }
        }
        if(trouver_ou_pas_2== Article_pas_trouver)
            pcc_verif.tab_verif_Article[k]= "NON";
        if(trouver_ou_pas_1== auteur_pas_trouver)
            pcc_verif.tab_verif_auteur[k]= "NON";

    }

    printf("%s\n", "elements de pcc auteur:");
    for(int i=0; i< pcc->size_pcc_auteur; i++)
    {
        printf("[%s]\n", pcc_verif.tab_verif_auteur[i]);
    }

    printf("%s\n", "elements de pcc Article:");
    for(int i=0; i< pcc->size_pcc_Article; i++)
    {
        printf("[%s]\n", pcc_verif.tab_verif_Article[i]);
    }


    free(pcc_verif.tab_verif_auteur);
    free(pcc_verif.tab_verif_Article);
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