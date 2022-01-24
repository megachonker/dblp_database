#include <stdio.h>
#include "../header/unwrap.h"
#include "../header/macro.h"
#include "../header/search.h"
#include <string.h>

#include "../header/fonctions_graphe.h"

#include "../header/list.h"

#include <regex.h>
#include <sys/types.h>

/**
 * @brief Get the top Article object
 * chaque etape je compare avec le premier element de ma pille
 * si il est plus grand j'ajoute
 * @param tout_article 
 * @param topX 
 * @return tab_Article_struct 
 */
tab_Article_struct get_top_Article(const tab_Article_struct *tout_article, int topX)
{
    INFO("get top %d des Article", topX);
    int indicepill = 0;
    Article_struct *pile = calloc(sizeof(Article_struct), topX);
    exitIfNull(pile, "imposible de faire la pille")

        Article_struct premier = {.nom_Article = "test",
                                  .nombre_auteur = 0};
    pile[0] = premier;

    for (int i = 0; i < tout_article->nombre_Article; i++)
    {
        PROGRESSBAR(i, tout_article->nombre_Article);
        if (pile[indicepill % topX].nombre_auteur < tout_article->tab_Article[i].nombre_auteur)
        {
            indicepill++;
            pile[indicepill % topX] = tout_article->tab_Article[i];
        }
    }
    tab_Article_struct top_article = {
        .nombre_Article = topX,
        .tab_Article = pile};
    return top_article;
}

tab_auteur_struct get_top_auteur(const tab_auteur_struct *tout_auteur, int topX)
{
    INFO("get top %d des auteur", topX);
    int indicepill = 0;
    auteur_struct *pile = calloc(sizeof(auteur_struct), topX);
    exitIfNull(pile, "imposible de faire la pille")

        auteur_struct premier = {.nom_auteur = "test",
                                 .size = 0};
    pile[0] = premier;

    for (int i = 0; i < tout_auteur->nombre_auteur; i++)
    {
        PROGRESSBAR(i, tout_auteur->nombre_auteur);
        if (pile[indicepill % topX].size < tout_auteur->tab_auteur[i].size)
        {
            indicepill++;
            pile[indicepill % topX] = tout_auteur->tab_auteur[i];
        }
    }
    tab_auteur_struct top_auteur = {
        .nombre_auteur = topX,
        .tab_auteur = pile};
    return top_auteur;
}

void scoarboard(const graphe_struct_Konqui *mongraph, const int getwhat, const int nbentrer,int verbositer)
{
    if (nbentrer < 0)
    {
        ERROR("nombre null ou négatif")
    }
    switch (getwhat)
    {
    case TOP_Article:
        INFO("Top %d des Article", nbentrer)
        tab_Article_struct monTopArticle = get_top_Article(&mongraph->tab_Article_struct, nbentrer);
        if(verbositer == verbeux)
            printList_Article(monTopArticle);
        break;
    case TOP_auteur:
        INFO("Top %d des auteur", nbentrer)
        tab_auteur_struct monTopauteur = get_top_auteur(&mongraph->tab_auteur_struct, nbentrer);
        if (verbositer == verbeux)
            printList_auteur(monTopauteur);
        break;
    default:
        break;
    }
}

/**
 * @brief pile
 * 
 * on bouger le pointeur jusqua reboucler ect ect
 * 
 * si on a pas asser de place on ralock
 * 
 */
typedef struct pille_auteur
{
    auteur_struct **auteur;
    size_t nmemb_alouer; ///<en nmbelement
    size_t nmemb_auteur; ///<est le nombre dauteur apres le pointeur
    size_t pointeur;     ///<le pointeur pointe au début de la pille
} pille_auteur;

void printPile(const pille_auteur *pile)
{
    //detecter le plus large
    int largeurmax = 0;
    for (size_t i = 0; i < pile->nmemb_auteur; i++)
    {
        int sizename = strlen(pile->auteur[i]->nom_auteur);
        if (sizename < largeurmax)
        {
            largeurmax = sizename;
        }
    }

    GREEN();
    printf("\n\n\n+");
    repchar('-', largeurmax - 2);
    printf("+\n");
    CLRCOLOR();
    for (size_t i = 0; i < pile->nmemb_auteur; i++)
    {
        int lenName = largeurmax - strlen(pile->auteur[i]->nom_auteur) - 2;
        GREEN();
        printf("|");
        YELLO();
        repchar(' ', lenName / 2);
        printf("%s", pile->auteur[i]->nom_auteur);
        repchar(' ', lenName / 2);
        GREEN();
        printf("|\n");
        CLRCOLOR();
    }
    GREEN();
    printf("+");
    repchar('-', largeurmax - 2);
    printf("+\n\n\n\n");
    CLRCOLOR();
}
//passer une 2eme
void explore(auteur_struct *auteurAexplorer, pille_auteur *pille)
{
    //on visite les article
    for (int i = 0; i < auteurAexplorer->nbArticlecontenue; i++)
    {
        //on visite les auteur
        WARNING("Auteur: %s", auteurAexplorer->tab_ptr_Article[i]->nom_Article);
        for (int u = 0; u < auteurAexplorer->tab_ptr_Article[i]->nombre_auteur; u++)
        {
            DEBUG("exploration de: %s", auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u]->nom_auteur)
            //check si pas déja explorer
            if (auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u]->auteur_parent)
                break;
            //on marque comme visiter
            auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u]->auteur_parent = auteurAexplorer;
            DEBUG("parent=>%s\n\tenfant:%s", auteurAexplorer->nom_auteur, auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u]->auteur_parent->nom_auteur);
            DEBUG("marquage:%p<=%p", auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u]->auteur_parent, auteurAexplorer);
            //on ajoute a la pille
            pille->auteur[pille->pointeur] = auteurAexplorer->tab_ptr_Article[i]->tab_ptr_auteur[u];
            pille->nmemb_auteur++;
            printPile(pille);
        }
    }
}

#define TAILLE_DEPARD 10

//fonction pour réalouer

void parcour_largeur(const graphe_struct_Konqui graph)
{

    auteur_struct *tabaddresseauteur = calloc(TAILLE_DEPARD, sizeof(pille_auteur *));
    exitIfNull(tabaddresseauteur, "imposible initialiser tableaux addresse")

        tabaddresseauteur[0] = graph.tab_auteur_struct.tab_auteur[0];
    tabaddresseauteur[0].auteur_parent = &tabaddresseauteur[0];

    pille_auteur pile = {.auteur = &tabaddresseauteur,
                         .nmemb_alouer = TAILLE_DEPARD,
                         .nmemb_auteur = 1};
    printPile(&pile);
    for (size_t i = 0; i < pile.nmemb_auteur; i++)
    {
        explore(pile.auteur[i], &pile);
        //on libere l'emplacement dans la pille
        pile.auteur[i] = NULL;
        pile.pointeur++;
        DEBUG("on avance de 1")
        printPile(&pile);
    }
}

ll_list *find_Article(const char *querry, const tab_Article_struct *tabarticle)
{
    INFO("FIND Article:")
    regex_t r;
    regcomp(&r, querry, REG_ICASE);

    ll_list *list = ll_create();
    list->type = typeArticle;

    for (int i = 0; i < tabarticle->nombre_Article; i++)
    {
        PROGRESSBAR(i, tabarticle->nombre_Article);
        if (!regexec(&r, tabarticle->tab_Article[i].nom_Article, 0, NULL, 0))
        {
            // WARNING("FounD: %s",tabarticle->tab_Article[i].nom_Article);
            ll_append(list, &tabarticle->tab_Article[i]);
        }
    }
    return list;
}

ll_list *find_auteur(const char *querry, const tab_auteur_struct *tabauteur)
{
    INFO("FIND auteur:")
    regex_t r;
    ll_list *list = ll_create();
    list->type = typeauteur;
    regcomp(&r, querry, REG_ICASE);
    for (int i = 0; i < tabauteur->nombre_auteur; i++)
    {
        PROGRESSBAR(i, tabauteur->nombre_auteur);
        if (!regexec(&r, tabauteur->tab_auteur[i].nom_auteur, 0, NULL, 0))
        {
            // WARNING("FounD: %s",tabauteur->tab_auteur[i].nom_auteur);
            ll_append(list, &tabauteur->tab_auteur[i]);
        }
    }
    return list;
}

ll_list *stringSearch(const graphe_struct_Konqui *mongraph, const int getwhat, const char *inputstr)
{
    switch (getwhat)
    {
    case searchArticle:
        INFO("Recherche %s dans les Article", inputstr)
        ll_list *ListeArticle = find_Article(inputstr, &mongraph->tab_Article_struct);
        return ListeArticle;
    case searchauteur:
        INFO("Recherche %s dans les auteur", inputstr)
        ll_list *Listeauteur = find_auteur(inputstr, &mongraph->tab_auteur_struct);
        return Listeauteur;
    case searchBoth:
        INFO("Recherche %s dans les auteur ET Article", inputstr)
        ll_list *both = ll_create();
        ll_list *ListeauteurBIS = find_auteur(inputstr, &mongraph->tab_auteur_struct);
        ll_list *ListeArticleBIS = find_Article(inputstr, &mongraph->tab_Article_struct);
        ll_append(both, ListeauteurBIS);
        ll_append(both, ListeArticleBIS);
        both->type = chaineArticleEtauteur;
        return both;
    default:
        ERROR(" pas bon mode")
        break;
    }
    return NULL;
}

int printSearch(ll_list *listchainer, int verbositer)
{
    if(listchainer == NULL){
        WARNING("faire une recherche concluante")
        return 1;
    }
    if (listchainer->type == typeArticle)
    {
        WARNING("SELECTION Article:")
        for (size_t i = 0; i < listchainer->size; i++)
        {
            Article_struct *article = ll_get(listchainer, i);
            INFO("%s", article->nom_Article)
            if (verbositer == silence)
                continue;
            for (int U = 0; U < article->nombre_auteur; U++)
            {
                DEBUG("%s", article->tab_ptr_auteur[U]->nom_auteur);
            }
            if (verbositer == VraimentTropVerbeux)
                explorearticle(article, 3);
        }
        WARNING("\t %ld Article", listchainer->size)
    }
    else if (listchainer->type == typeauteur)
    {
        WARNING("SELECTION auteur:")
        for (size_t i = 0; i < listchainer->size; i++)
        {
            auteur_struct *auteur = ll_get(listchainer, i);
            INFO("%s", auteur->nom_auteur)
            if (verbositer == silence)
                continue;
            for (int U = 0; U < auteur->nbArticlecontenue; U++)
            {
                DEBUG("%s", auteur->tab_ptr_Article[U]->nom_Article);
                if (verbositer == VraimentTropVerbeux)
                    explorearticle(auteur->tab_ptr_Article[U], 3);
            }
        }
        WARNING("\t %ld auteur", listchainer->size)
    }
    else if (listchainer->type == chaineArticleEtauteur)
    {
        WARNING("SELECTION Article ET auteur:")
        DEBUG("la chaine contien %i element", (int)listchainer->size)
        for (size_t i = 0; i < listchainer->size; i++)
        {

            // if (!ll_get(listchainer, i))
            // {
            //     ERROR("liste chainer %ld vide", i)
            //     continue;
            // }
            
            printSearch(ll_get(listchainer, i), silence);
        }
    }else{
        DEBUG("JSP ! %d",listchainer->type)
    }
    return 0;
}

int parse_arg(char *input, char **output)
{
    char *pch;
    pch = strtok(input, " ");
    int counter = 0;
    output[counter] = pch;
    //   strcat(output[counter],NULL);
    YOLO("%s (%i)", output[counter], counter)
    while (pch != NULL)
    {
        counter++;
        pch = strtok(NULL, " ");
        output[counter] = pch;
        YOLO("%s (%i)", output[counter], counter)
    }
        YOLO("len %ld",strlen(output[counter-1])-1)
    output[counter-1][strlen(output[counter-1])-1]='\0';
        YOLO("$$%s (%i)", output[counter-1], counter)

    return counter;
}


ll_list * researchArticle(ll_list * malisteArticle,int action, regex_t r){
    DEBUG("researchArticle")
    for (size_t i = 0; i < malisteArticle->size; i++)
    {
        PROGRESSBAR(i, malisteArticle->size);
        Article_struct * monarticle =  ll_get(malisteArticle,i);
        int match = regexec(&r, monarticle->nom_Article, 0, NULL, 0);
        if (action == blacklist && !match)
        {
            // DEBUG("researchArticle-blacklist: remove item")
            ll_remove(malisteArticle,i);
            i--;
        }else if (action == whitelist && match)
        {
            // DEBUG("researchArticle-whitelist: remove item")
            ll_remove(malisteArticle,i);
            i--;
        }
    }
    return malisteArticle;
}

ll_list * researchauteur(ll_list * malisteauteur,int action, regex_t r){
    DEBUG("researchauteur")
    for (size_t i = 0; i < malisteauteur->size; i++)
    {
        PROGRESSBAR(i, malisteauteur->size);
        auteur_struct * monauteur =  ll_get(malisteauteur,i);
        int match = regexec(&r, monauteur->nom_auteur, 0, NULL, 0);
        if (action == blacklist && !match)
        {
            // DEBUG("researchauteur-blacklist: remove item")
            ll_remove(malisteauteur,i);
            i--;
        }else if (action == whitelist && match)
        {
            // DEBUG("researchauteur-whitelist: remove item")
            ll_remove(malisteauteur,i);
            i--;
        }
    }
    return malisteauteur;
}

void restringSearch(ll_list * mesRecherch, const int typederecherche, const char *inputstr){
    DEBUG("restringSearch")
    regex_t r;
    regcomp(&r, inputstr, REG_ICASE);
    
    if (mesRecherch->type == chaineArticleEtauteur)
    {
        for (size_t i = 0; i < mesRecherch->size; i++)
        {
            DEBUG("Redirection")
            restringSearch(ll_get(mesRecherch, i),typederecherche,inputstr);
        }
    }else if (mesRecherch->type == typeArticle)
    {
        researchArticle(mesRecherch,typederecherche,r);
    }else{
        researchauteur(mesRecherch,typederecherche,r);
    }
}




