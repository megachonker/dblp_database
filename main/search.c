#include <stdio.h>
#include <unwrap.h>
#include "macro.h"

unwrap_Graph_struct * graph;

enum{
    TOP_Article,
    TOP_auteur
}
search(char * auteurA, char * auteurB){

}

sort(){

}


/**
 * @brief Get the top Article object
 * chaque etape je compare avec le premier element de ma pille
 * si il est plus grand j'ajoute
 * @param tout_article 
 * @param topX 
 * @return tab_Article_struct 
 */
tab_Article_struct get_top_Article(const tab_Article_struct * tout_article,int topX){
    INFO("get top %d des Article",topX);
    int indicepill=0;
    topX%indicepill;
    Article_struct * pile = calloc(sizeof(Article_struct),topX);
    exitIfNull(pile,"imposible de faire la pille")

    Article_struct premier ={premier.nom_Article  = "test",
                            premier.nombre_auteur = 0};
    pile[0] = premier;

    for (int i = 0; i < tout_article->nombre_Article; i++)
    {
        progressbar(i,tout_article->nombre_Article);
        if (pile[topX%indicepill].nombre_auteur < tout_article->tab_Article[i].nombre_auteur)
        {
            indicepill++;
            pile[topX%indicepill] = tout_article->tab_Article[i];
        }
    }
    tab_Article_struct top_article = {
            top_article.nombre_Article = topX,
            top_article.tab_Article = pile};
    return top_article;
}


// get_top_auteur(){

// }

scoarboard(unwrap_Graph_struct * mongraph , int getwhat ,int nbentrer){
    switch (getwhat)
    {
    case TOP_Article:
        tab_Article_struct monTop = get_top_Article(mongraph->tab_Article_struct,nbentrer);
        printList_Article(&monTop);
        break;
    case TOP_auteur:

        break;

    default:
        break;
    }
}

