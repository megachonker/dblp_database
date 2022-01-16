#include <stdio.h>
#include "unwrap.h"
#include "macro.h"
#include "search.h"

// unwrap_Graph_struct * graph;


// search(char * auteurA, char * auteurB){

// }

// sort(){

// }


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
    Article_struct * pile = calloc(sizeof(Article_struct),topX);
    exitIfNull(pile,"imposible de faire la pille")

    Article_struct premier ={.nom_Article  = "test",
                            .nombre_auteur = 0};
    pile[0] = premier;

    for (int i = 0; i < tout_article->nombre_Article; i++)
    {
        progressbar(i,tout_article->nombre_Article);
        if (pile[indicepill%topX].nombre_auteur < tout_article->tab_Article[i].nombre_auteur)
        {
            indicepill++;
            pile[indicepill%topX] = tout_article->tab_Article[i];
        }
    }
    tab_Article_struct top_article = {
                .nombre_Article = topX,
                .tab_Article = pile};
    return top_article;
}


tab_auteur_struct get_top_auteur(const tab_auteur_struct * tout_auteur,int topX){
    INFO("get top %d des auteur",topX);
    int indicepill=0;
    auteur_struct * pile = calloc(sizeof(auteur_struct),topX);
    exitIfNull(pile,"imposible de faire la pille")

    auteur_struct premier ={.nom_auteur  = "test",
                            .size = 0};
    pile[0] = premier;

    for (int i = 0; i < tout_auteur->nombre_auteur; i++)
    {
        progressbar(i,tout_auteur->nombre_auteur);
        if (pile[indicepill%topX].size < tout_auteur->tab_auteur[i].size)
        {
            indicepill++;
            pile[indicepill%topX] = tout_auteur->tab_auteur[i];
        }
    }
    tab_auteur_struct top_auteur = {
                .nombre_auteur = topX,
                .tab_auteur = pile};
    return top_auteur;
}

void scoarboard(const unwrap_Graph_struct * mongraph ,const int getwhat ,const int nbentrer){
    switch (getwhat)
    {
    case TOP_Article:
        INFO("Top %d des Article",nbentrer)
        tab_Article_struct monTopArticle = get_top_Article(mongraph->tab_Article_struct,nbentrer);
        printList_Article(&monTopArticle);
        break;
    case TOP_auteur:
        INFO("Top %d des auteur",nbentrer)
        tab_auteur_struct monTopauteur = get_top_auteur(mongraph->tab_auteur_struct,nbentrer);
        printList_auteur(&monTopauteur);
        break;

    default:
        break;
    }
}

