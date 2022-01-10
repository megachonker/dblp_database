#ifndef _graphe_test_
#define _graphe_test_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"


//Je crée 10 auteurs ayant écrit des Articles, 9 Articles crées de toutes pieces de la même façon
auteur_struct** creation_graphe_test(Article_struct** tab_Articles_test) //tab_Articles est le tableau de pointeur vers les Articles du graphe test
{
    auteur_struct a0;
    auteur_struct a1;
    auteur_struct a2;
    auteur_struct a3;
    auteur_struct a4;
    auteur_struct a5;
    auteur_struct a6;
    auteur_struct a7;
    auteur_struct a8;
    auteur_struct a9;

    Article_struct A0;
    Article_struct A1;
    Article_struct A2;
    Article_struct A3;
    Article_struct A4;
    Article_struct A5;
    Article_struct A6;
    Article_struct A7;
    Article_struct A8;

    a0.nom_auteur= "a0";
    a0.size= 1;
    a0.tab_ptr_Article= malloc(sizeof(Article_struct*));
    a0.tab_ptr_Article[0]= &A7;

    a1.nom_auteur= "a1";
    a1.size= 1;
    a1.tab_ptr_Article= malloc(sizeof(Article_struct*));
    a1.tab_ptr_Article[0]= &A7;

    a2.nom_auteur= "a2";
    a2.size= 1;
    a2.tab_ptr_Article= malloc(sizeof(Article_struct*));
    a2.tab_ptr_Article[0]= &A8;

    a3.nom_auteur= "a3";
    a3.size= 2;
    a3.tab_ptr_Article= malloc(sizeof(Article_struct*)*2);
    a3.tab_ptr_Article[0]= &A5;
    a3.tab_ptr_Article[1]= &A6;

    a4.nom_auteur= "a4";
    a4.size= 3;
    a4.tab_ptr_Article= malloc(sizeof(Article_struct*)*3);
    a4.tab_ptr_Article[0]= &A0;
    a4.tab_ptr_Article[1]= &A2;
    a4.tab_ptr_Article[2]= &A7;

    a5.nom_auteur= "a5";
    a5.size= 2;
    a5.tab_ptr_Article=malloc(sizeof(Article_struct*)*2);
    a5.tab_ptr_Article[0]= &A1;
    a5.tab_ptr_Article[1]= &A2;

    a6.nom_auteur= "a6";
    a6.size= 2;
    a6.tab_ptr_Article=malloc(sizeof(Article_struct*)*2);
    a6.tab_ptr_Article[0]= &A0;
    a6.tab_ptr_Article[1]= &A6;

    a7.nom_auteur= "a7";
    a7.size= 4;
    a7.tab_ptr_Article=malloc(sizeof(Article_struct*)*4);
    a7.tab_ptr_Article[0]= &A4;
    a7.tab_ptr_Article[1]= &A5;
    a7.tab_ptr_Article[2]= &A6;
    a7.tab_ptr_Article[3]= &A7;

    a8.nom_auteur= "a8";
    a8.size= 2;
    a8.tab_ptr_Article= malloc(sizeof(Article_struct*)*2);
    a8.tab_ptr_Article[0]= &A1;
    a8.tab_ptr_Article[1]= &A2;

    a9.nom_auteur= "a9";
    a9.tab_ptr_Article= malloc(sizeof(Article_struct*)*3);
    a9.tab_ptr_Article[0]= &A1;
    a9.tab_ptr_Article[1]= &A3;
    a9.tab_ptr_Article[2]= &A5;



    A0.nom_Article= "A0";
    A0.nombre_auteur= 2;
    A0.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*2);
    A0.tab_ptr_auteur[0]= &a4;
    A0.tab_ptr_auteur[1]= &a6;

    A1.nom_Article= "A1";
    A1.nombre_auteur= 2;
    A1.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*2);
    A1.tab_ptr_auteur[0]= &a5;
    A1.tab_ptr_auteur[1]= &a9;

    A2.nom_Article= "A2";
    A2.nombre_auteur= 2;
    A2.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*2);
    A2.tab_ptr_auteur[0]= &a4;
    A2.tab_ptr_auteur[1]= &a5;

    A3.nom_Article= "A3";
    A3.nombre_auteur= 2;
    A3.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*2);
    A3.tab_ptr_auteur[0]= &a9;
    A3.tab_ptr_auteur[1]= &a8;

    A4.nom_Article= "A4";
    A4.nombre_auteur= 2;
    A4.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*2);
    A4.tab_ptr_auteur[0]= &a8;
    A4.tab_ptr_auteur[1]= &a7;

    A5.nom_Article= "A5";
    A5.nombre_auteur= 3;
    A5.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*3);
    A5.tab_ptr_auteur[0]= &a9;
    A5.tab_ptr_auteur[1]= &a3;
    A5.tab_ptr_auteur[2]= &a7;

    A6.nom_Article= "A6";
    A6.nombre_auteur= 3;
    A6.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*3);
    A6.tab_ptr_auteur[0]= &a7;
    A6.tab_ptr_auteur[1]= &a6;
    A6.tab_ptr_auteur[2]= &a3;

    A7.nom_Article= "A7";
    A7.nombre_auteur= 4;
    A7.tab_ptr_auteur=malloc(sizeof(auteur_struct*)*4);
    A7.tab_ptr_auteur[0]= &a4;
    A7.tab_ptr_auteur[1]= &a1;
    A7.tab_ptr_auteur[2]= &a0;
    A7.tab_ptr_auteur[3]= &a7;

    A8.nom_Article= "A8";
    A8.nombre_auteur= 1;
    A8.tab_ptr_auteur=malloc(sizeof(auteur_struct*));
    A8.tab_ptr_auteur[0]= &a2;

    
    tab_Articles_test= malloc(sizeof(Article_struct*)*9);
    tab_Articles_test[0]= &A0;
    tab_Articles_test[1]= &A1;
    tab_Articles_test[2]= &A2;
    tab_Articles_test[3]= &A3;
    tab_Articles_test[4]= &A4;
    tab_Articles_test[5]= &A5;
    tab_Articles_test[6]= &A6;
    tab_Articles_test[7]= &A7;
    tab_Articles_test[8]= &A8;
    
    
    auteur_struct** graphe_test= malloc(sizeof(auteur_struct*)*10);
    graphe_test[0]=&a0;
    graphe_test[1]=&a1;
    graphe_test[2]=&a2;
    graphe_test[3]=&a3;
    graphe_test[4]=&a4;
    graphe_test[5]=&a5;
    graphe_test[6]=&a6;
    graphe_test[7]=&a7;
    graphe_test[8]=&a8;
    graphe_test[9]=&a9;

    return graphe_test;
}


void free_graphe_test(auteur_struct** graphe_test, Article_struct** tab_Articles_test)
{
    for(int i=0; i<10; i++)
    {
        free(graphe_test[i]->tab_ptr_Article);
    }
    free(graphe_test);

    for(int i=0; i<9; i++)
    {
       free(tab_Articles_test[i]->tab_ptr_auteur); 
    }
    free(tab_Articles_test);

}

#endif