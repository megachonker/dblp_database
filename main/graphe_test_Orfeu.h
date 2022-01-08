#ifndef _graphe_test_
#define _graphe_test_

#include <stdio.h>
#include "unwrap.h"
#include "list.h"
#include <stdlib.h>
#include "creation_graphe_voisins.h"


//Je crée des 10 auteurs ayant écrit des Articles
//Je crée aussi les Articles ayant leur tableau d'auteur 

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
A8.nomre_auteur= 1;
A8.tab_ptr_auteur=malloc(sizeof(auteur_struct*));
A8.tab_ptr_auteur[0]= &a2;


void free_tout(void)
{
    
    free(a0.tab_ptr_Article);
    free(a1.tab_ptr_Article);
    free(a2.tab_ptr_Article);
    free(a3.tab_ptr_Article);
    free(a4.tab_ptr_Article);
    free(a5.tab_ptr_Article);
    free(a6.tab_ptr_Article);
    free(a7.tab_ptr_Article);
    free(a8.tab_ptr_Article);
    free(a9.tab_ptr_Article);

    
    free(A0.tab_ptr_auteur);
    free(A1.tab_ptr_auteur);
    free(A2.tab_ptr_auteur);
    free(A3.tab_ptr_auteur);
    free(A4.tab_ptr_auteur);
    free(A5.tab_ptr_auteur);
    free(A6.tab_ptr_auteur);
    free(A7.tab_ptr_auteur);
    free(A8.tab_ptr_auteur);


}









#endif