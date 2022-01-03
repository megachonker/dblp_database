#include<stdio.h>
#include "parsing.h"
#include "list-makefile-2/linked-list.h"
#include "creation_Gt.h"









//ligne 178 de creatio,_Gt, j'ai mis une *, je comprend pas pk j'ai du faire ça pour pas avoir d'erreur





void afficher_liste(ll_list *liste)
{
    ll_node *it_liste=liste->first;

    for(size_t k=0; k<liste->size; k++)
    {
        //printf("%s\n", "afficher_Gt_liste boucle");
        printf("[%s]", (char*)(it_liste->value));
        it_liste=it_liste->next;
    }
    printf("%c", '\n');
}


void afficher_Gt(ll_list *Gt)
{
    ll_node *it_Gt=Gt->first;
    
    printf("%li\n", Gt->size);
    
    for(size_t i=0; i<Gt->size; i++)
    {
        //printf("%s\n", "afficher_Gt boucle");
        afficher_liste(it_Gt->value);
        it_Gt=it_Gt->next;
    }

}


int main(void)
{
    
    
    
    
    
    fiche_minimale A0;

    A0.liste_auteur = malloc(3*sizeof(char*));
    if(A0.liste_auteur==NULL)
    {
        printf("%s\n", "erreur de malloc");
        exit(1);
    }
    A0.liste_auteur[0]="a0";
    A0.liste_auteur[1]="a1";
    A0.liste_auteur[2]="a2";
    A0.nombre_auteur=3;

    
    fiche_minimale A1;

    A1.liste_auteur = malloc(1*sizeof(char*));
    if(A1.liste_auteur==NULL)
    {
        printf("%s\n", "erreur de malloc");
        exit(1);
    }
    A1.liste_auteur[0]="a3";
    A1.nombre_auteur=1;


    fiche_minimale A2;

    A2.liste_auteur = malloc(2*sizeof(char*));
    if(A2.liste_auteur==NULL)
    {
        printf("%s\n", "erreur de malloc");
        exit(1);
    }

    A2.liste_auteur[0]="a4";
    A2.liste_auteur[1]="a5";
    A2.nombre_auteur=2;

    tableaux_fiche tab_fiche_situation1;

    tab_fiche_situation1.fiche=malloc(3*sizeof(fiche_minimale));
    if(tab_fiche_situation1.fiche==NULL)
    {
        printf("%s\n", "erreur de malloc");
        exit(1);
    }
    tab_fiche_situation1.fiche[0]=&A0;
    tab_fiche_situation1.fiche[1]=&A1;
    tab_fiche_situation1.fiche[2]=&A2;
    tab_fiche_situation1.taille=3;

    ll_list *Gt=creation_Gt(&tab_fiche_situation1);


    afficher_Gt(Gt);
    //printf("%s\n", "OK");
    
    free(Gt);

    /*free(A0.liste_auteur[0]);
    free(A0.liste_auteur[1]);
    free(A0.liste_auteur[2]);*/
    free(A0.liste_auteur);
    
    //free(A1.liste_auteur[0]);
    free(A1.liste_auteur);

    /*free(A2.liste_auteur[0]);
    free(A2.liste_auteur[1]);*/
    free(A2.liste_auteur);

    free(tab_fiche_situation1.fiche);

    return 0;
}






