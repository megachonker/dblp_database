#ifndef UNWRAP
#define UNWRAP
// #include "unwrap.h" ///< j'include 
#include "parsing.h"
// #include "list.h"


/**
 * @brief couple Hauteur <=> Heuvre
 * utiliser pour qsort donc interne
 */
typedef struct Paire_HauteurHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
}Paire_HauteurHeurvre;


struct Sommet_Article_TableauxD;

/**
 * @brief Un hauteur plusieur heuvre
 * 
 * Générée a partire des cache
 */
typedef struct Sommet_Auteur_TableauxD
{
    struct Sommet_Article_TableauxD ** pointeur_Article; ///La magie qui pointe sur  Sommet_Article_TableauxD
    int nbelementmagi;      ///<compteur d'élément Sommet_Article_TableauxD
    char * hauteur;         ///<chaine de caractere maloc
    fiche_minimal ** heuvre;///<tableaux dynamique d'adresse pointant sur des structure contenant oeuvre
    int size;               ///<taille du tableaux dynamique
}Sommet_Auteur_TableauxD;

/**
 * @brief Un Article a plusieur Auteur
 * 
 * Chaque Article pointe vers fiche_minimal de la on peut y retrouver le titre de l'article
 * Chaque article pointe ver plusieur Auteur qui provienne de Sommet_Auteur_TableauxD de la on peut y retrouver  l'auteur
 * 
 * Sommet_Auteur_TableauxD on peut ce rediriger ver une autre fiche
 * 
 */
typedef struct Sommet_Article_TableauxD
{
    char * Article; ///< générée par deserialisation Contien toute les info d'un article\n qui provienne du parsing
    Sommet_Auteur_TableauxD ** pointeur_Auteur_tableaux; ///< Liste de pointeur (meme indice que liste_auteur ) qui reboucle sur Sommet_Auteur_TableauxD avec sont auteur
    int nombre_Auteur;
}Sommet_Article_TableauxD;

/**
 * @brief liste déplier pour le trie
 * 
tableaux_Somet_hauteur *tableaux_Somet_hauteur dans article on a la le nombre de d'euvre
 * 
 */
typedef struct Paire_ArticleHauteur
{
    //si lordre de mes article est le meme que tableaux_fiche
    //allor si j'accede au Xeme Article de tableaux_fiche
    //allor je peut acceder au Xeme element de Sommet_Article_TableauxD
    //Donc Sommet_Auteur_TableauxD ayant chaque hauteur pointant sur 
    char * article; ///< dans la fiche minimal on va y retrouver le noms de l'article
    Sommet_Auteur_TableauxD * pointeur_Auteur; ///< pointe ver un auteur Sommet_Auteur_TableauxD
}Paire_ArticleHauteur;





/**
 * @brief Stoque tout les Sommet_Auteur_TableauxD
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur Sommet_Auteur_TableauxD
 * ainsie que le nombre d'élément (Sommet_Auteur_TableauxD) stoquer dans le tableaux 
 */
typedef struct List_Auteur
{
    Sommet_Auteur_TableauxD * tableaux_Somet_hauteur;// LISTE DADRESE DONC ** ??????????????????????
    int taille;
}List_Auteur;

/**
 * @brief Contien Sommet_Article_TableauxD est le nombre d'article 
 * 
 * 
 */
 typedef struct List_Article
{
    Sommet_Article_TableauxD * pointeur_Article_tableaux; ///< liste de pointeur qui pointe ver Sommet_Article_TableauxD
    int nombre_Article;
}List_Article;

/**
 * @brief Structure contenant toute les structure importante
 * 
 * 
 */
typedef struct unwrap_Graph
{
    List_Auteur * list_Auteur;
    List_Article * list_Article;
    tableaux_fiche * tableaux_de_fiche;
}unwrap_Graph;



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
 * @brief Affiche hauteur <=> Heuvre
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
 * qui est une association auteur <=> heuvre unique
 * 
 * @param [in]  input toute les fiche des oeuvre qui comporte les liste auteur  
 * @param [out] arrayout liste qui associe un auteur a une oeuvre
 * @return nombre d'élément du tableaux
 */
int SwapStruct(tableaux_fiche input, Paire_HauteurHeurvre * arrayout );

/**
 * @brief génère List_Auteur a partire de Paire_HauteurHeurvre
 * 
 * fonction pricipal elle parcoure Paire_HauteurHeurvre est quand le meme
 * auteur ce suit ajoute tout les oeuvre dans un nouveaux tableaux
 * 
 * @param [in] liste                liste trier par auteur des paire auteur titre
 * @param [in] sizeHauteurHeuvre    taille de cette liste
 * @return List_Auteur* addressse de la liste final générée Auteur to Multiple titre  
 */
List_Auteur* gen_List_Auteur(const Paire_HauteurHeurvre * liste,int sizeHauteurHeuvre);

/**
 * @brief Affiche la liste final d'Auteur To multiple Titre
 * 
 * @param [in] OwO une addresse
 */
void printList_Auteur(List_Auteur * OwO);



/**
 * @brief génère un index des auteur a partire d'un fichier
 * 
 * il faudrait pouvoir détecter le type de fichier mais de base on assume que ces une liste a inverser
 * 
 * @param [in] inputFile fichier générer par serialize() 
 * @return List_Auteur* Structure  
 */
List_Auteur * unwrap_from_file(FILE * inputFile);


// /**
//  * @brief DéPRéCIER! voir unwrap_Serilise_Index
//  * 
//  * Serialise la structeur List_Auteur
//  * 
//  * @param [in] List_des_Auteur 
//  * @param [out] output
//  */
// void unwrap_Serilise(const List_Auteur * List_des_Auteur, FILE * output);

// /**
//  * @brief DéPRéCIER! voir unwrap_Deserilise_Index
//  * 
//  * désérialise l'index des Auteur depuis un fichier
//  * 
//  * 
//  * @param [in] input => unwrap_serilise file 
//  * @return List_Auteur*
//  */
// List_Auteur * unwrap_Deserilise(FILE * input);


/**
 * @brief sérialisation de List_Auteur
 * 
 * # Sera écrit:
 * - noms hauteur
 * - nombre d'article
 * - indice article 
 * *on va écrire ADDR (l'indice) qui est l'indice pour acceder a fiche_minimal en fesant Sommet_Auteur_TableauxD[ADDR]*
 * 
 * @param [in] List_des_Auteur le titre de l'heuvre accesible avec List_Auteur=>Sommet_Auteur_TableauxD=>fiche_minimal => ADDR
 * @param [out] output fichier de sortie 
 */
void unwrap_Serilise_Index(const List_Auteur * List_des_Auteur, FILE * output);

/**
 * @brief désérialise une un cache produit par unwrap_Serilise_Index
 * 
 * 
 * 
 * tableaux_fiche
 * @param [in] List_des_Auteur deserialisation de la bonne fiche l'heuvre fiche[ADDR] 
 * @param [out] input on va pouvoir trouver ADDR et ne noms de l'auteur 
 * @return List_Auteur* 
 */
List_Auteur * unwrap_Deserilise_Index(const tableaux_fiche * List_des_Auteur, FILE * input);


// void unwrap_sinc(List_Auteur * List_des_Auteur ,const tableaux_fiche input);
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
// void unwrap_resolve(List_Auteur * List_des_Auteur, Sommet_Auteur_TableauxD * resove, const tableaux_fiche * input);

// /**
//  * @brief D2PR3CIER génère une liste chainer a partire d'un tableaux
//  * 
//  * 
//  * @param input 
//  * @param list_chainer_auteur 
//  */
// void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur );



unwrap_Graph gen_unwrap_Graph(FILE * dblpxml, FILE * inverted);


void printList_Article(List_Article * OwO);

void unwrap_List_Auteur_free(List_Auteur * free);

#endif