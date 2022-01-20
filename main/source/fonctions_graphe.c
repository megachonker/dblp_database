#include <stdio.h>
#include <stdlib.h>
#include "../header/unwrap.h"
#include "../header/fonctions_graphe.h"


graphe_struct_Konqui faire_graphe_Konqui(char * DBfiche, char * DBauteur, char * DBArticle)
{
    INFO("tests:deserialisation")

    FILE * DBficheLecture   = fopen(DBfiche     ,"r");
    FILE * DBauteurLecture  = fopen(DBauteur    ,"r");
    FILE * DBArticleLecture = fopen(DBArticle   ,"r");
    
    graphe_struct_Konqui graphe_Konqui = deserialise_Graph(DBficheLecture
                                    ,DBauteurLecture
                                    ,DBArticleLecture);

    exitIfNull(DBficheLecture  ,"erreur ouverture bd")
    exitIfNull(DBauteurLecture ,"erreur ouverture bd")
    exitIfNull(DBArticleLecture,"erreur ouverture bd")

    fclose(DBficheLecture);
    fclose(DBauteurLecture);
    fclose(DBArticleLecture);

    return graphe_Konqui;
}



//faire le graphe (tableau) des pointeurs vers les auteurs, ce que je vais appeler ensuite graphe_Katie
graphe_struct_Katie faire_graphe_ptr_auteur( graphe_struct_Konqui graphe_Konqui)
{

    int size_graphe= graphe_Konqui.tab_auteur_struct->nombre_auteur;
    
    graphe_struct_Katie graphe_struct;
    graphe_struct.graphe= malloc(sizeof(auteur_struct*)*size_graphe);
    exitIfNull(graphe_struct.graphe,"erreur malloc graphe_Katie");
    graphe_struct.size_graphe= size_graphe;

    for(int i=0; i<size_graphe; i++)
    {
        auteur_struct* ai_ptr= &(graphe_Konqui.tab_auteur_struct->tab_auteur[i]);
        ai_ptr->size_pcc_auteur= -1;
        ai_ptr->ptr_Article_predecesseur_pcc= NULL;
        ai_ptr->ptr_auteur_predecesseur_pcc= NULL;
        graphe_struct.graphe[i]= ai_ptr;
    }
    return graphe_struct;
}


//Je vérifie que les auteurs du chemin sont bien voisins 2 à 2 dans l'ordre du chemin
//et que les Articles du pcc sont bien cohérent avec le pcc auteur
//si c'est le cas, un "OK" sera affiché à la l'indice de l'auteur / Article
void verifier_do_Dijkstra(plus_court_chemin_struct* pcc)
{
    pcc_struct_verification pcc_verif;
    pcc_verif.tab_verif_auteur= malloc(sizeof(char*)*pcc->size_pcc_auteur);
    pcc_verif.tab_verif_Article= malloc(sizeof(char*)*pcc->size_pcc_Article);
    
    pcc_verif.tab_verif_auteur[0]= "OK";

    for(int k=0; k< pcc->size_pcc_auteur-1; k++) //pour tout les auteurs ak du pcc (plus court chemin)
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


void voir_si_un_auteur_est_dans_le_graphe_et_donner_un_Article_ou_il_apparait(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else 
    {
        printf("%s apparait dans le graphe, il est par exemple l'auteur de l'Article: %s\n", nom_auteur, ptr_auteur->tab_ptr_Article[0]->nom_Article);        
    }
}

void donner_tous_les_Articles_de_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else
    {
        printf("%s apparait dans le graphe, il est l'auteur des l'Articles: \n", nom_auteur);
        for(int k=0; k< ptr_auteur->size; k++)
        {
            printf("%s\n", ptr_auteur->tab_ptr_Article[k]->nom_Article);
        }
    }
}

void donner_tous_ceux_qui_ont_travalle_avec_auteur(graphe_struct_Katie graphe_struct, char* nom_auteur)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    auteur_struct* ptr_auteur= NULL;
    
    for(int i=0; i<graphe_struct.size_graphe; i++)
    {
        if(strcmp(nom_auteur, graphe_struct.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas= auteur_trouver;
            ptr_auteur= graphe_struct.graphe[i];
            
        }
    }
    if(trouver_ou_pas== auteur_pas_trouver)
    {
        printf("%s n'apparait dans aucun Article\n", nom_auteur);   
    }
    else
    {
        printf("%s a déjà écrit un Article avec:\n", nom_auteur);
    
        for(int l=0; l< ptr_auteur->size; l++)
        {

            Article_struct* ptr_Al= ptr_auteur->tab_ptr_Article[l];

            for(int k=0; k< ptr_Al->nombre_auteur; k++)
            {
                auteur_struct* ptr_collegue= ptr_Al->tab_ptr_auteur[k];
                printf("%s\n", ptr_collegue->nom_auteur);

            }
        }
    }
}


