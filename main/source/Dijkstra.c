

#include <stdio.h>
#include "../header/unwrap.h"
#include <stdlib.h>
#include <string.h>
#include "../header/fonctions_graphe.h"
#include "../header/Dijkstra.h"




//fonction de debug: la pile courante est un tableau où se trouve les auteurs à traiter à l'étape courante dans Dijkstra 
//(les auteurs sont représentés par leur attribut indice_dans_le_graphe)
void print_pile_courante(int* pile_indice, int size, auteur_struct** graphe)
{
    printf("%s\n", "pile courante:");
    for(int k=0; k< size; k++)
    {
        char* nom_auteur= graphe[pile_indice[k]]->nom_auteur;
        printf("%s\n", nom_auteur);
        
    }
    printf("\n");
    printf("%s\n", graphe[pile_indice[0]]->nom_auteur);
    printf("\n\n\n");
}

//même fonction, mais pour la pile suivante t(ableau des auteurs à traiter à l'étape suivante de Dijkstra)
void print_pile_suivante(int* pile_indice, int size, auteur_struct** graphe)
{
    printf("%s\n", "pile suivante:");
    for(int k=0; k< size; k++)
    {
        char* nom_auteur= graphe[pile_indice[k]]->nom_auteur;
        printf("%s\n", nom_auteur);
        
    }
    printf("\n");
    printf("%s\n", graphe[pile_indice[0]]->nom_auteur);
    printf("\n\n\n");
}

void print_auteur_indice(auteur_struct** graphe, int size)
{
    for(int k=0; k<size; k++)
    {
        printf("%s:%d\n", graphe[k]->nom_auteur, graphe[k]->indice_dans_le_graphe);
    }
    printf("\n");
}

//afficher le pcc (plus court chemin) en auteur et en Article
void print_chemins_auteur_et_Article(plus_court_chemin_struct* pcc)
{
    
    //graphe_struct_Katie mon_graphe= faire_graphe_ptr_auteur();

    if(pcc!=NULL)
    {
        WARNING("chemin auteur:");
        for(int i=0; i< pcc->size_pcc_auteur; i++)
        {
            GREY();fprintf(stderr,"\t\t\t%s\n", pcc->pcc_tab_ptr_auteur[i]->nom_auteur);CLRCOLOR();
        }
        WARNING("chemin Article");
        for(int i=0; i< pcc->size_pcc_Article; i++)
        {
            GREY();fprintf(stderr,"\t\t\t%s\n", pcc->pcc_tab_ptr_Article[i]->nom_Article);CLRCOLOR();
        }
    }
}


/*****************************************************************************************************************************************************/
//A partir d'ici on a la fonction Dijkstra et ses sous fonctions



//renvoie le tableau des ptr vers les auteur_struct du chemin de auteur_1 (a1) a auteur_2 (a2)
plus_court_chemin_struct* do_Dijkstra(graphe_struct_Katie graphe_t, char* nom_auteur_depart, char* nom_auteur_destination)
{
    INFO("verification existance de la paire d'auteur dans le graph")

    comparaison_auteur trouver_ou_pas_1= auteur_pas_trouver;
    comparaison_auteur trouver_ou_pas_2= auteur_pas_trouver;
    auteur_struct* ptr_auteur_depart= NULL;
    auteur_struct* ptr_auteur_destination= NULL;

    for(int i=0; i<graphe_t.size_graphe; i++)
    {
        PROGRESSBAR(i,graphe_t.size_graphe);
        graphe_t.graphe[i]->indice_dans_le_graphe= i;

        if(strcmp(nom_auteur_depart, graphe_t.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas_1= auteur_trouver;
            ptr_auteur_depart= graphe_t.graphe[i];
        }

        if(strcmp(nom_auteur_destination, graphe_t.graphe[i]->nom_auteur)==0)
        {
            trouver_ou_pas_2= auteur_trouver;
            ptr_auteur_destination= graphe_t.graphe[i];
        }
    }

    if(trouver_ou_pas_1== auteur_pas_trouver)
        printf("%s %s %s\n", "l'auteur", nom_auteur_depart, "ne figure dans aucun Article");

    if(trouver_ou_pas_2== auteur_pas_trouver)
        printf("%s %s %s\n", "l'auteur", nom_auteur_destination, "ne figure dans aucun Article");

    //si l'un des auteurs n'est pas dans la base de donnée, on renvoie un chemin NULL
    if(trouver_ou_pas_1== auteur_pas_trouver || trouver_ou_pas_2== auteur_pas_trouver)
        return NULL;


    //si les 2 auteurs sont dans le graphe, on applique Dijkstra pour trouver le plus court chemin 
    //les  auteur->size_plus_court_chemins sont deja set up a -1 dans (fonctions_graphe.c)
    
    plus_court_chemin_struct* plus_court_chemin= relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(ptr_auteur_depart, ptr_auteur_destination, nom_auteur_depart, graphe_t);
    
    //cas ou j'ai tout parcouru et que j'ai pas trouvé de chemin
    if(plus_court_chemin== NULL)
        return NULL;

    return plus_court_chemin;
}


// "traiter l'auteur courant" siginifie mettre a jour les attributs de tous ses voisins
plus_court_chemin_struct* relachement_de_arretes_jusqu_a_trouver_ou_tout_parcourir(auteur_struct* ptr_auteur_depart, auteur_struct* ptr_auteur_destination, char* nom_auteur_depart, graphe_struct_Katie graphe_t)
{
    //les piles, sont des tableau d'indice d'auteur, (indice dans le graphe)
    //les piles vont accueillir les auteurs à traiter à chaque étape du parcours en largeur.
    int* pile_auteur_a_traiter_etape_courante= calloc(graphe_t.nb_auteurMax,sizeof(int));
    exitIfNull(pile_auteur_a_traiter_etape_courante, "echec malloc pile_auteur_a_traiter_etape_courante");
    
    int* pile_suivante= calloc(graphe_t.nb_auteurMax,sizeof(int));
    exitIfNull(pile_suivante, "echec malloc pile_suivante");
    
    pile_auteur_a_traiter_etape_courante[0]= ptr_auteur_depart->indice_dans_le_graphe;
    int haut_de_pile_courante=1;
    int haut_de_pile_suivante=0;
    int* haut_de_pile_courante_ptr= &haut_de_pile_courante;
    int* haut_de_pile_suivante_ptr= &haut_de_pile_suivante;

    ptr_auteur_depart->size_pcc_auteur= 0;
    
    
    int compteurprofondeur = 0;
    
    int taille_pcc=1; //=profondeur du parcour en largeur (à la fin, =taille du plus court chemin)
    int* taille_pcc_ptr= &taille_pcc;
    INFO("Exploration profondeur: ")
    while(pile_auteur_a_traiter_etape_courante[0]!= -1)
    {
        fprintf(stderr,"\033[100D\t\t");
        GREEN();fprintf(stderr,"couche %d...",compteurprofondeur);

        compteurprofondeur++;

        for(int i=0; i< *haut_de_pile_courante_ptr; i++)
        {
            auteur_struct* ptr_auteur_courant= graphe_t.graphe[pile_auteur_a_traiter_etape_courante[i]];

            if(ptr_auteur_courant== ptr_auteur_destination)
            {
                free(pile_auteur_a_traiter_etape_courante);
                free(pile_suivante);


                plus_court_chemin_struct* pcc_ptr= calloc(1,sizeof(plus_court_chemin_struct));
                plus_court_chemin_struct pcc= reconstitution_du_pcc_apres_parcours(taille_pcc_ptr, ptr_auteur_destination);
                *pcc_ptr= pcc;
                fprintf(stderr,"\n");
                return pcc_ptr;
            }
            traitement_auteur_courant_et_mise_a_jour_pile_suivante(ptr_auteur_courant, haut_de_pile_suivante_ptr, taille_pcc_ptr, pile_suivante);   
        }
        

        //on vide la pile courante
        //(une pile vide est constituée de -1)

        for(int j=0; j< *haut_de_pile_courante_ptr; j++)
        {
            pile_auteur_a_traiter_etape_courante[j]= -1;
        }
        *haut_de_pile_courante_ptr= 0;   

        //si la pile suivante est vide on met à -1 le premier element de la pile courante,
        //signe que l'on a traité tous les auteurs de la composante connexe explorée
        if(pile_suivante[0]== -1)
        { 
            pile_auteur_a_traiter_etape_courante[0]= -1;
        }
        else  //sinon, on remplie la pile courante avec les indice d'auteur de la pile suivante 
        {
            for(int t=0; t< *haut_de_pile_suivante_ptr; t++)
            {
                pile_auteur_a_traiter_etape_courante[t]= pile_suivante[t];
            }
            *haut_de_pile_courante_ptr= *haut_de_pile_suivante_ptr;
        }

        //on vide la pile suivante
        for(int i=0; i< *haut_de_pile_suivante_ptr; i++)
        {
            pile_suivante[i]= -1;
        }
        *haut_de_pile_suivante_ptr=0;
        (*taille_pcc_ptr)++;
       
        //    printf("val %d pile_courante: %d\n", k, pile_auteur_a_traiter_etape_courante[k]);
        //}
        //printf("fin d'une étape profondeur\n");
    
    }

    free(pile_auteur_a_traiter_etape_courante);
    free(pile_suivante);
    WARNING("\nIl n'y a pas de chemin entre %s et %s\n", nom_auteur_depart, ptr_auteur_destination->nom_auteur);
    return NULL;
}


//"traiter l'auteur courant" siginifie mettre a jour la size_pcc_auteur de tous ses voisins 
//(voir la structure auteur_struct pour plus de detaille sur size_pcc_auteur)
void traitement_auteur_courant_et_mise_a_jour_pile_suivante(auteur_struct* ptr_auteur_courant, int* haut_de_pile_suivante_ptr, int* taille_pcc_ptr, int* pile_suivante)
{
    //pour tous les Articles Al de l'auteur_courant
    for(int l=0; l< ptr_auteur_courant->size; l++)
    { 
        Article_struct* ptr_Article_l= ptr_auteur_courant->tab_ptr_Article[l];

        //pour tous les auteur ak dans Al 
        //(ak étant le voisin_k de l'auteur courant)
        for(int k=0; k< ptr_Article_l->nombre_auteur; k++)
        {
            auteur_struct* ptr_voisin_k= ptr_Article_l->tab_ptr_auteur[k];
           
            //Si Dijkstra n'est pas encore passé par ak (ak, le voisin_k de l'auteur_courant)
            if(ptr_voisin_k->size_pcc_auteur== -1 ) 
            {
                pile_suivante[*haut_de_pile_suivante_ptr]= ptr_voisin_k->indice_dans_le_graphe;
                *haut_de_pile_suivante_ptr= *haut_de_pile_suivante_ptr+1;
            
                //on met à jour ak->size_pcc_auteur
                ptr_voisin_k->size_pcc_auteur= *taille_pcc_ptr;

                //On set up l'auteur_predecesseur de ak
                ptr_voisin_k->ptr_auteur_predecesseur_pcc= ptr_auteur_courant;
                //On set up l'Article_predecesseur de voisin_k
                ptr_voisin_k->ptr_Article_predecesseur_pcc= ptr_Article_l;               
            }
        }       
    }
}


//une fois qu'on a trouvé l'auteur destination en faisant le parcours en largeur, on a initialisé les pédécesseurs sur le pcc (plus court chemin),
//on a plus qu'a remplir le pcc en partant de l'auteur destination et en suivant les predecesseurs
plus_court_chemin_struct reconstitution_du_pcc_apres_parcours(int* taille_pcc_ptr, auteur_struct* ptr_auteur_destination)
{
    plus_court_chemin_struct plus_court_chemin;
    plus_court_chemin.size_pcc_auteur= (*taille_pcc_ptr);
    plus_court_chemin.size_pcc_Article= (*taille_pcc_ptr)-1;

    plus_court_chemin.pcc_tab_ptr_auteur= calloc(*taille_pcc_ptr,sizeof(auteur_struct*));

    exitIfNull(plus_court_chemin.pcc_tab_ptr_auteur,"echec calloc pcc_tab_ptr_auteur"); 

    plus_court_chemin.pcc_tab_ptr_Article= calloc(((*taille_pcc_ptr)-1),sizeof(Article_struct*));
    exitIfNull(plus_court_chemin.pcc_tab_ptr_Article,"echec calloc pcc_tab_ptr_Article"); 

    //on remplie le pcc avec les auteurs et Articles emprunté
    plus_court_chemin.pcc_tab_ptr_auteur[(*taille_pcc_ptr)-1]= ptr_auteur_destination;
    
    auteur_struct* ptr_auteur_it= ptr_auteur_destination;
    for(int t=(*taille_pcc_ptr)-2; t>=0; t--)
    {
        plus_court_chemin.pcc_tab_ptr_auteur[t]= ptr_auteur_it->ptr_auteur_predecesseur_pcc;
        plus_court_chemin.pcc_tab_ptr_Article[t]= ptr_auteur_it->ptr_Article_predecesseur_pcc;

        ptr_auteur_it= ptr_auteur_it->ptr_auteur_predecesseur_pcc;   
    }

    return plus_court_chemin;
}

//fonction qui renvoie un flag si l'auteur passé en argument se trouve dans la pile passé en argument
comparaison_auteur trouver_ou_pas_dans_pile(int* haut_de_pile_suivante, int* pile_indice, auteur_struct* ptr_auteur, auteur_struct** graphe)
{
    comparaison_auteur trouver_ou_pas= auteur_pas_trouver;
    for(int k=0; k< *haut_de_pile_suivante; k++)
    {
        if(graphe[pile_indice[k]]==ptr_auteur)
            trouver_ou_pas= auteur_trouver;
    }

    return trouver_ou_pas;
}



void free_Dijkstra(graphe_struct_Katie graphe_struct, plus_court_chemin_struct *pcc_ptr)
{
    INFO("Free Dijkstra ")
    if(pcc_ptr!= NULL)
    {  
        free(pcc_ptr->pcc_tab_ptr_auteur);
        free(pcc_ptr->pcc_tab_ptr_Article);
        free(pcc_ptr);
    }
    free(graphe_struct.graphe);


    // for(int k=0; k< graphe_struct.size_graphe; k++)
    // {
    //     free(graphe_struct.graphe[k]->ptr_Article_predecesseur_pcc);
    //     free(graphe_struct.graphe[k]->ptr_auteur_predecesseur_pcc);
    // }


}






/**
 * @brief PAS DE MAIN ICI
 * 
 * a la compilation il n'y a que un main tolérer hors il faut utilicer cette biblioteque
 * donc ce programe ne dois pas avoir de main
 * 
 */

//je test Dijkstra sur mon graphe test en affichant les noms des auteurs du plus court chemin de a0 a a9
// int main(void)
// {   
//     //FILE* graphe_test_Katie= fopen("DATA", "r");

                                                       //cache_fiche 
    //fichiers en cache de la base de donnée en entier //auteur_cache
                                                       //Article_cache

//     //cache_ficheO  ;
//     //auteur_cacheO ;
//     //Article_cacheO;

//     //cache_fiche 
//     //auteur_cache
//     //Article_cache


//     graphe_struct_Konqui graphe_Konqui= faire_graphe_Konqui(cache_fiche, auteur_cache, Article_cache);

//     graphe_struct_Katie graphe_Katie= faire_graphe_ptr_auteur(graphe_Konqui);

//     //fclose(graphe_test_Katie);
    
//     //char* nom_auteur_depart= mon_graphe.graphe[1344]->nom_auteur;
//     //printf("nom auteur_depart: %s\n", nom_auteur_depart);

//     //char* nom_auteur_destination= mon_graphe.graphe[8888]->nom_auteur;
//     //printf("nom auteur_destination: %s\n", nom_auteur_destination);

//     char* nom_auteur_depart= graphe_Katie.graphe[1234]->nom_auteur;
//     char* nom_auteur_destination= graphe_Katie.graphe[8888]->nom_auteur;
//     //voir convention pour ecrire les accents: https://sites.psu.edu/symbolcodes/codehtml/#accent
//     plus_court_chemin_struct* plus_court_chemin=  do_Dijkstra(graphe_Katie, nom_auteur_depart, nom_auteur_destination);

    
//     if(plus_court_chemin!= NULL)
//     {
//         print_chemins_auteur_et_Artice(plus_court_chemin);

//         verifier_do_Dijkstra(plus_court_chemin);
//     }

//    free_Dijkstra(&graphe_Katie, plus_court_chemin);
    
    

   
    
//     return 0;
// }
