#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"
#include "graphe_test_Katie.h"

typedef enum a_mettre_dans_voisins_ou_pas
{
    a_ne_pas_mettre,
    a_mettre

}a_mettre_dans_voisins_ou_pas;



unwrap_Graph_struct do_unwrap_graphe(int* size_graphe_ptr)
{
    FILE * DBxml = fopen("DATA/SerializedStruc.data","r");
    FILE * DBinverse = fopen("DATA/SerializedStrucInverse.data","r");

    unwrap_Graph_struct unwrap_Graph  =    gen_unwrap_Graph(DBxml, DBinverse); //< erreur peut etre la ?
    
    fclose(DBxml);
    fclose(DBinverse);

    
    int *size_graphe_ptr= malloc(sizeof(int));
    *size_graphe_ptr= unwrap_Graph.tab_auteur_struct->taille;

    return unwrap_Graph;
}



//graphe= tableau des ptr vers les auteur_struct avec pour chacun, leur tableau de ptr vers leurs voisins
auteur_struct** creation_graphe(void)
{
    /*int* size_graphe_ptr=NULL;
    unwrap_Graph_struct unwrap_graphe= do_unwrap_graphe(size_graphe_ptr);*/


    auteur_struct* graphe_test= creation_graphe_test();
    int *size_graphe_ptr=NULL;
    *size_graphe_ptr=10;
    

    //creation du graphe sans les voisins
    auteur_struct** graphe=malloc(sizeof(auteur_struct*)**size_graphe_ptr);
    if(graphe== NULL)
    {
        printf("%s\n", "erreur de malloc du graphe");
        return NULL;
    }
    
    for(int i=0; i<*size_graphe_ptr; i++)
    {
        auteur_struct ai= graphe_test[i]; /*unwrap_Graph.tab_auteur_struct->tab_auteur[i];*/
        graphe[i]= &ai;
    }


    //ajout du tableau des voisins pour chaque auteur

    //pour tous les auteurs ak du graphe
    for(int k=0; k<*size_graphe_ptr; k++)
    {
        auteur_struct *ptr_ak= graphe[k];
        
        ptr_ak->tab_voisins= malloc(sizeof(auteur_struct*));
        if(ptr_ak->tab_voisins== NULL)
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


                    auteur_struct *ptr_an= ptr_ak->tab_voisins[n];

                    if(ptr_am== ptr_an)
                        flag= a_ne_pas_mettre;


                }

                if(flag== a_mettre)
                {
                    nb_actuel_voisins++;
                    ptr_ak->tab_voisins=realloc(ptr_ak->tab_voisins, sizeof(auteur_struct*)*nb_actuel_voisins);
                    ptr_ak->tab_voisins[nb_actuel_voisins-1]= ptr_am;
                   
                }



            }


        }
        
        ptr_ak->nb_voisins= nb_actuel_voisins;
        ptr_ak->etiquette=-1; //on set up toutes les etiquettes a -1 en prevision pour Dijkstra



    }

    return graphe;
}


void free_graphe(auteur_struct** graphe, int* size_graphe_ptr)
{
    for(int k=0; k<*size_graphe_ptr; k++)
    {
        auteur_struct *ptr_ak= graphe[k];
        
        
        free(ptr_ak->tab_voisins);
        free(ptr_ak);
    }

    free(size_graphe_ptr);
}


//test: affichage des voisins des auteurs du graphe_test
int main(void)
{
    
    auteur_struct **graphe=creation_graphe();
    for(int i=0; i< 10; i++)
    {
    
        int nb_voisin= graphe[i]->nb_voisins;
        char* nom_auteur= graphe[i]->nom_auteur;
        printf("voisins de %s :\n", nom_auteur);
        
        for(int k=0; k <nb_voisin; k++)
        {
            char *nom_voisin= graphe[i]->tab_voisins[k]->nom_auteur;
            printf("%s\n", nom_voisin);
        }
    }

    int* size_graphe_ptr=NULL;
    *size_graphe_ptr=10;

    free_graphe(graphe, size_graphe_ptr);


    
    
    return 0;
}