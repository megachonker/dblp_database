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
auteur_struct** faire_graphe_ptr_auteur(FILE *file_xml)
{
    
    tab_auteur_struct * malistauteur= gen_tab_auteur_from_xml_et_liaison_article(file_xml);
    
    int size_graphe_ptr= malistauteur->nombre_auteur;
    graphe_t graphe_struct;
    graphe_struct.graphe= malloc(sizeof(auteur_struct*)**size_graphe_ptr);
    graphe_struct.size_graphe= *size_graphe_ptr;

    for(int i=0; i<*size_graphe_ptr; i++)
    {
        printf("%s", malistauteur->tab_auteur[i].nom_auteur);
    }
    printf("%s", "\n\n\n");



    for(int i=0; i<*size_graphe_ptr; i++)
    {
        auteur_struct ai= malistauteur->tab_auteur[i];
        ai.size_pcc_auteur= -1;
        graphe[i]= &ai;
    }

    free(malistauteur);

    return graphe;
}


/*
//graphe= tableau des ptr vers les auteur_struct avec pour chacun, leur tableau de ptr vers leurs voisins
auteur_struct** creation_graphe_avec_voisins(auteur_struct** graphe, int* ptr_size_graphe)
{
    //ajout du tableau des voisins pour chaque auteur
    //pour tous les auteurs ak du graphe
    for(int k=0; k<*ptr_size_graphe; k++)
    {
        
        auteur_struct *ptr_ak= graphe[k];
        printf("%s%c\n", "auteur",k);
        
        ptr_ak->tab_ptr_voisins= malloc(sizeof(auteur_struct*));
        if(ptr_ak->tab_ptr_voisins== NULL)
        {
            printf("%s%i\n", "erreur de malloc du tableau des voisins de ags",k);
            return NULL;
        }

        int nb_actuel_voisins= 0;

        //pour tous les Articles Al écrit par l'auteur courant ak
        for(int l=0; l< ptr_ak->size; l++)
        {
            
            int nbr_a_dans_Al= ptr_ak->tab_ptr_Article[l]->nombre_auteur; 

            //pour tous les auteurs am, de l'article courant écrit par l'auteur courant ak
            for(int m=0; m<nbr_a_dans_Al; m++)
            {


                   
                //initialisation du flag pour savoir si il faut mettre l'auteur am dans la liste des voisins de agk
                a_mettre_dans_voisins_ou_pas flag= a_mettre;
                
                auteur_struct *ptr_am= ptr_ak->tab_ptr_Article[l]->tab_ptr_auteur[m]; 

                if(ptr_am== ptr_ak) //on pourra remplacer les comparaisons de pointeur par des comparaison d'id pour opti
                    flag= a_ne_pas_mettre;
                
                
                //on verifie si am est pas deja dans les voisins an de ak
                for(int n=0; n<nb_actuel_voisins; n++)
                {


                    auteur_struct *ptr_an= ptr_ak->tab_ptr_voisins[n];

                    if(ptr_am== ptr_an)
                        flag= a_ne_pas_mettre;


                }

                if(flag== a_mettre)
                {
                    nb_actuel_voisins++;
                    printf("%s%i\n", "nb_voisin_actuel:", nb_actuel_voisins);
                    ptr_ak->tab_ptr_voisins=realloc(ptr_ak->tab_ptr_voisins, sizeof(auteur_struct*)*nb_actuel_voisins);
                    ptr_ak->tab_ptr_voisins[nb_actuel_voisins-1]= ptr_am;
                   
                }



            }


        }
        
        ptr_ak->nb_voisins= nb_actuel_voisins;
       



    }

    return graphe;
}


void free_graphe_avec_voisins(auteur_struct** graphe_avec_voisins, int* size_graphe_ptr)
{
    for(int k=0; k<*size_graphe_ptr; k++)
    {
        auteur_struct* ptr_ak= graphe_avec_voisins[k];
        
        
        free(ptr_ak->tab_ptr_voisins);
        free(ptr_ak);
    }
    free(graphe_avec_voisins);
}
*/

//test: affichage des voisins des auteurs du graphe_test
int main(void)
{

    FILE* graphe_test_Katie= fopen("DATA/test_Katie.xml", "r");

    auteur_struct** graphe= faire_graphe_ptr_auteur(size_ptr, graphe_test_Katie);

    fclose(graphe_test_Katie);

  
    for(int k=0; k <*size_ptr; k++)
    {
        char *nom_auteur= graphe[k]->nom_auteur;
        printf("%s\n", nom_auteur);
    }

    free(graphe);
    

    
    
    return 0;
}
