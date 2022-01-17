#ifndef UNWRAP
#define UNWRAP
#include "parsing.h"
#include "macro.h"

/**
 * @brief couple nom_auteur <=> oeuvre
 * utiliser pour qsort donc interne
 */
typedef struct Paire_auteur_oeuvre
{
    char * nom_auteur;
    fiche_minimale * oeuvre;
}Paire_auteur_oeuvre;


struct Article_struct;

/**
 * @brief Un nom_auteur plusieur oeuvre
 * 
 * Générée a partire des caches
 */
typedef struct auteur_struct
{
    struct Article_struct ** tab_ptr_Article; ///La magie qui pointe sur  Article_struct
    int nbArticlecontenue;      ///<compteur d'élément Article_struct
    int indiceDeCreation;
    char * nom_auteur;
    fiche_minimale ** tab_ptr_fiche_min;///<tableaux dynamique d'adresse pointant sur des structure contenant oeuvre
    int size;                           ///<taille du tableaux dynamique
    

    struct auteur_struct * auteur_parent;


    //ajoue d'Katie de ce qui est utile pour Dijkstra
    struct auteur_struct* ptr_auteur_predecesseur_pcc; //auteur predecesseur dans le plus court chemin
    struct Article_struct* ptr_Article_predecesseur_pcc; //auteur predecesseur dans le plus court chemin
    int size_pcc_auteur; // distance en nombre d'auteur pour passer de l'auteur de depart a l'auteur d'arriver
    
    int nbmembreTabarticleALOUER;
}auteur_struct;

/**
 * @brief Un Article a plusieurs auteur
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
    // fiche_minimale * fiche_lier;///<fiche minimal lier a cette article 
    int nombre_auteur;
}Article_struct;

/**
 * @brief liste déplier pour le trie
 * 
tab_auteur *tab_auteur dans article on a la le nombre de d'euvre
 * 
 */
typedef struct Paire_Article_auteur
{
    //si lordre de mes article est le meme que tableaux_fiche
    //allor si j'accede au Xeme Article de tableaux_fiche
    //allor je peut acceder au Xeme element de Article
    //Donc auteur ayant chaque nom_auteur pointant sur 
    char * article; ///< dans la fiche minimal on va y retrouver le noms de l'article
    auteur_struct * pointeur_Auteur; ///< pointe ver un auteur auteur
}Paire_Article_auteur;

/**
 * @brief Stoque tout les auteur
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur auteur
 * ainsie que le nombre d'élément (auteur) stoquer dans le tableaux 
 */
typedef struct tab_auteur_struct
{
    auteur_struct * tab_auteur;
    int nombre_auteur;
    int nombre_article;
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
    tableaux_fiche tableaux_de_fiche;
}unwrap_Graph_struct;

/**
 * @brief Affiche nom_auteur <=> oeuvre
 * 
 * @param [in] OwI  Paire_auteur_oeuvre
 * @param [in] sizeauteuroeuvre nombre d'élément 
 */
void printPaire_auteurHeurvre(Paire_auteur_oeuvre * OwI,int sizeauteuroeuvre );

/**
 * @brief Affiche la liste final d'auteur To multiple Titre
 * 
 * @param [in] OwO une addresse
 */
void printList_auteur(tab_auteur_struct * OwO);

void printList_Article(tab_Article_struct * OwO);

/**
 * @brief génère un index des auteur a partire d'un fichier
 * 
 * il faudrait pouvoir détecter le type de fichier mais de base on assume que ces une liste a inverser
 * 
 * @param [in] inputFile fichier générer par serialisation_tableaux_fiche() 
 * @return tab_auteur_struct* Structure  
 */
tab_auteur_struct * tab_auteur_from_file(FILE * inputFile);

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
void serialise_tab_auteur_struct(const tab_auteur_struct * List_des_Auteur, FILE * output);

/**
 * @brief désérialise une un cache produit par serialise_tab_auteur_struct
 * 
 * 
 * 
 * tableaux_fiche
 * @param [in] List_des_Auteur deserialisation de la bonne fiche l'oeuvre fiche[ADDR] 
 * @param [out] input on va pouvoir trouver ADDR et ne noms de l'auteur 
 * @return tab_auteur_struct* 
 */
tab_auteur_struct * deserialise_tab_auteur_struct(const tableaux_fiche * List_des_Auteur, FILE * input);



unwrap_Graph_struct deserialise_Graph(FILE * dbxmlCache, FILE * auteurCache, FILE * ArticleCache);
unwrap_Graph_struct gen_Graph_from_XML(FILE * dbxmlCache);
void serialise_Graph(unwrap_Graph_struct graph, FILE * dbxmlCache, FILE * auteurCache, FILE * ArticleCache);




void unwrap_List_Auteur_free(tab_auteur_struct * free);

tab_Article_struct * gen_tab_Article_from_xml(FILE * dbinput);

void serialisation_tab_Article_struct(tab_Article_struct * inputlist, FILE * outputfile);

tab_Article_struct * deserialisation_tab_Article_struct(tab_auteur_struct * mesauteur, FILE * inputfile);

tab_Article_struct * convertTab_auteur2Article(const tab_auteur_struct * Malistauteur);

tab_auteur_struct * gen_tab_auteur_from_xml(FILE * dbinput);

void test_exploration_Article(const tab_Article_struct * mesarticle);

tab_auteur_struct * gen_tab_auteur_from_xml_et_liaison_article(FILE * dbinput);

#endif