#ifndef UNWRAP
#define UNWRAP
// #include "unwrap.h" ///< j'include 
#include "parsing.h"
// #include "list.h"


/**
 * @brief couple nom_auteur <=> Heuvre
 * utiliser pour qsort donc interne
 */
typedef struct Paire_HauteurHeurvre
{
    char * nom_auteur;
    fiche_minimale * oeuvre;
}Paire_HauteurHeurvre;


struct Article_struct;

/**
 * @brief Un nom_auteur plusieur oeuvre
 * 
 * Générée a partire des cache
 */
typedef struct auteur_struct
{
    struct Article_struct ** tab_ptr_Article; ///La magie qui pointe sur  Article_struct
    int nbelementmagi;      ///<compteur d'élément Article_struct
    char * nom_auteur;
    fiche_minimale ** tab_ptr_fiche_min;///<tableaux dynamique d'adresse pointant sur des structure contenant oeuvre
    int size;                           ///<taille du tableaux dynamique
    
    //ajoue d'Katie
    struct auteur_struct **tab_voisins;        //tableau de pointeur vers les voisins de l'auteur
    int nb_voisins;
    int etiquette;
    
}auteur_struct;

/**
 * @brief Un Article a plusieur auteur
 * 
 * Chaque Article pointe vers fiche_minimal de la on peut y retrouver le titre de l'article
 * Chaque article pointe ver plusieur auteur qui provienne de auteur de la on peut y retrouver  l'auteur
 * 
 * auteur on peut ce rediriger ver une autre fiche
 * 
 */
typedef struct Article_struct
{
    char * nom_Article; ///< générée par deserialisation Contien toute les info d'un article\n qui provienne du parsing
    auteur_struct ** tab_ptr_auteur; ///< Liste de pointeur (meme indice que liste_auteur ) qui reboucle sur auteur avec sont auteur
    int nombre_Auteur;
}Article_struct;

/**
 * @brief liste déplier pour le trie
 * 
tab_auteur *tab_auteur dans article on a la le nombre de d'euvre
 * 
 */
typedef struct Paire_ArticleHauteur
{
    //si lordre de mes article est le meme que tableaux_fiche
    //allor si j'accede au Xeme Article de tableaux_fiche
    //allor je peut acceder au Xeme element de Article
    //Donc auteur ayant chaque nom_auteur pointant sur 
    char * article; ///< dans la fiche minimal on va y retrouver le noms de l'article
    auteur_struct * pointeur_Auteur; ///< pointe ver un auteur auteur
}Paire_ArticleHauteur;





/**
 * @brief Stoque tout les auteur
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur auteur
 * ainsie que le nombre d'élément (auteur) stoquer dans le tableaux 
 */
typedef struct tab_auteur_struct
{
    auteur_struct * tab_auteur;
    int taille;
}tab_auteur_struct;

/**
 * @brief Contien nom_Article est le nombre d'article 
 * 
 * 
 */
 typedef struct tab_Article_struct
{
    Article_struct * tab_Article;
    int nombre_Article;
}tab_Article_struct;

/**
 * @brief Structure contenant toute les structure importante
 * 
 * 
 */
typedef struct unwrap_Graph_struct
{
    tab_auteur_struct * tab_auteur_struct;
    tab_Article_struct * tab_Article_struct;
    tableaux_fiche * tableaux_de_fiche;
}unwrap_Graph_struct;



/**
 * @brief fonction de comparaison pour qsort
 * 
 * elle pourait être mieux
 * 
 * @param [in] a object A
 * @param [in] b object B
 * @return int 
 */
int comphauteur(const void * a, const void * b);

/**
 * @brief Affiche nom_auteur <=> Heuvre
 * 
 * @param [in] OwI  Paire_HauteurHeurvre
 * @param [in] sizeHauteurHeuvre nombre d'élément 
 */
void printPaire_HauteurHeurvre(Paire_HauteurHeurvre * OwI,int sizeHauteurHeuvre );


/**
 * @brief génère un tableaux d' HauteurToHeurvre 
 * 
 * déplie tableaux_fiche pour généré unt tableaux
 * d'élément Paire_HauteurHeurvre
 * qui est une association auteur <=> oeuvre unique
 * 
 * @param [in]  input toute les fiche des oeuvre qui comporte les liste auteur  
 * @param [out] arrayout liste qui associe un auteur a une oeuvre
 * @return nombre d'élément du tableaux
 */
int SwapStruct(tableaux_fiche input, Paire_HauteurHeurvre * arrayout );

/**
 * @brief génère tab_auteur_struct a partire de Paire_HauteurHeurvre
 * 
 * fonction pricipal elle parcoure Paire_HauteurHeurvre est quand le meme
 * auteur ce suit ajoute tout les oeuvre dans un nouveaux tableaux
 * 
 * @param [in] liste                liste trier par auteur des paire auteur titre
 * @param [in] sizeHauteurHeuvre    taille de cette liste
 * @return tab_auteur_struct* addressse de la liste final générée auteur to Multiple titre  
 */
tab_auteur_struct* gen_List_Auteur(const Paire_HauteurHeurvre * liste,int sizeHauteurHeuvre);

/**
 * @brief Affiche la liste final d'auteur To multiple Titre
 * 
 * @param [in] OwO une addresse
 */
void printList_Auteur(tab_auteur_struct * OwO);



/**
 * @brief génère un index des auteur a partire d'un fichier
 * 
 * il faudrait pouvoir détecter le type de fichier mais de base on assume que ces une liste a inverser
 * 
 * @param [in] inputFile fichier générer par serialize() 
 * @return tab_auteur_struct* Structure  
 */
tab_auteur_struct * unwrap_from_file(FILE * inputFile);


// /**
//  * @brief DéPRéCIER! voir unwrap_Serilise_Index
//  * 
//  * Serialise la structeur tab_auteur_struct
//  * 
//  * @param [in] List_des_Auteur 
//  * @param [out] output
//  */
// void unwrap_Serilise(const tab_auteur_struct * List_des_Auteur, FILE * output);

// /**
//  * @brief DéPRéCIER! voir unwrap_Deserilise_Index
//  * 
//  * désérialise l'index des auteur depuis un fichier
//  * 
//  * 
//  * @param [in] input => unwrap_serilise file 
//  * @return tab_auteur_struct*
//  */
// tab_auteur_struct * unwrap_Deserilise(FILE * input);


/**
 * @brief sérialisation de tab_auteur_struct
 * 
 * # Sera écrit:
 * - noms nom_auteur
 * - nombre d'article
 * - indice article 
 * *on va écrire ADDR (l'indice) qui est l'indice pour acceder a fiche_minimal en fesant auteur[ADDR]*
 * 
 * @param [in] List_des_Auteur le titre de l'oeuvre accesible avec tab_auteur_struct=>auteur=>fiche_minimal => ADDR
 * @param [out] output fichier de sortie 
 */
void unwrap_Serilise_Index(const tab_auteur_struct * List_des_Auteur, FILE * output);

/**
 * @brief désérialise une un cache produit par unwrap_Serilise_Index
 * 
 * 
 * 
 * tableaux_fiche
 * @param [in] List_des_Auteur deserialisation de la bonne fiche l'oeuvre fiche[ADDR] 
 * @param [out] input on va pouvoir trouver ADDR et ne noms de l'auteur 
 * @return tab_auteur_struct* 
 */
tab_auteur_struct * unwrap_Deserilise_Index(const tableaux_fiche * List_des_Auteur, FILE * input);


// void unwrap_sinc(tab_auteur_struct * List_des_Auteur ,const tableaux_fiche input);
// /**
//  * @brief 
//  * 
//  * 
//  * n'ayant pas les object Euvre/auteur
//  *  apres la décérialisation
//  *  ajout fonction résolution qui va ajouterune entrée a chaque foit qu'on l'interroge
//  *  de magnierre a ce qu'il soit possible d'executer l'algo sans avoir tout résolut
//  *
//  *  néamoins recalculer depuit from file est plus rapide ...
//  * 
//  * @param List_des_Auteur 
//  * @param resove 
//  * @param input 
//  */
// void unwrap_resolve(tab_auteur_struct * List_des_Auteur, auteur_struct * resove, const tableaux_fiche * input);

// /**
//  * @brief D2PR3CIER génère une liste chainer a partire d'un tableaux
//  * 
//  * 
//  * @param input 
//  * @param list_chainer_auteur 
//  */
// void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur );



unwrap_Graph_struct gen_unwrap_Graph(FILE * dblpxml, FILE * inverted);


void printList_Article(tab_Article_struct * OwO);

void unwrap_List_Auteur_free(tab_auteur_struct * free);

tab_Article_struct * unwrap_ListArticle_from_xml(FILE * dbinput);

#endif