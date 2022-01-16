#include <stdio.h>
#include <stdlib.h>
#include "fonctions_graphe.h"
#include "unwrap.h"
#include "test.h"



typedef enum a_mettre_dans_voisins_ou_pas
{
    a_ne_pas_mettre,
    a_mettre

}a_mettre_dans_voisins_ou_pas;


//on appelera "graphe" le tableau de ptr d'auteur correspondant a unwrap_Graph
//avant d'appeler cette fonction, il faut fopen DBxml et déclarer le pointeur size_graphe_ptr
//et après faut close le file
auteur_struct** faire_graphe_avec_unwrap_graphe(int* size_graphe_ptr, FILE *DBxml, FILE *DBinverse, char* chemin_vers_cache_fichier_xml)
{
    
    
    tab_auteur_struct * malistauteur = unwrap_from_file(DBxml);
    serialise_tab_auteur_struct(malistauteur,DBinverse);
    unwrap_List_Auteur_free(malistauteur);
    
    fclose(DBinverse);
    FILE * DBinvers_re = fopen(chemin_vers_cache_fichier_xml, "r");
    // tab_Article_struct * matable = unwrap_ListArticle_from_xml(DBxml);

    unwrap_Graph_struct unwrap_Graph= gen_unwrap_Graph(DBxml, DBinvers_re); //< erreur peut etre la ?
    
    
    fclose(DBinvers_re);

    //creation du tableau de ptr d'auteur correspondant a unwrap_Graph
    *size_graphe_ptr= unwrap_Graph.tab_auteur_struct->taille;
    auteur_struct** graphe= malloc(sizeof(auteur_struct*)**size_graphe_ptr);
    if(graphe== NULL)
    {
        printf("%s\n", "erreur de malloc du graphe");
        return NULL;
    }
    
    for(int i=0; i<*size_graphe_ptr; i++)
    {
        auteur_struct ai= unwrap_Graph.tab_auteur_struct->tab_auteur[i];
        ai.size_pcc_auteur= -1;
        graphe[i]= &ai;
        printf("%s", ai.nom_auteur);
    }

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
    
    int *size_ptr= NULL;

    FILE* DBinverse= fopen(serializedbunwrap, "w");
    
    FILE* DBxml= fopen(originedb, "r");

    auteur_struct** graphe= faire_graphe_avec_unwrap_graphe(size_ptr, DBxml, DBinverse, , );
    
    fclose(test_xml);
    fclose(DBinverse);

  
    for(int k=0; k <*size_ptr; k++)
    {
        char *nom_auteur= graphe[k]->nom_auteur;
        printf("%s\n", nom_auteur);
    }
    


    

    
    
    return 0;
}
