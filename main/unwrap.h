#ifndef UNWRAP
#define UNWRAP

#include "parsing.h"
#include "list.h"

typedef struct Paire_HauteurHeurvre
{
    char * hauteur;
    fiche_minimal * heuvre;
}Paire_HauteurHeurvre;


/**
 * @brief Un hauteur plusieur heuvre
 * 
 */
typedef struct Sommet_Auteur_TableauxD
{
    char * hauteur;
    fiche_minimal ** heuvre;///<tableaux dynamique d'adresse pointant sur des structure contenant oeuvre
    int size;               ///<taille du tableaux dynamique
}Sommet_Auteur_TableauxD;


/**
 * @brief Stoque tout les Sommet_Auteur_TableauxD
 * 
 * sous forme de tableaux DYNAMIQUE d'adresse pointant sur Sommet_Auteur_TableauxD
 * ainsie que le nombre d'élément (Sommet_Auteur_TableauxD) stoquer dans le tableaux 
 */
typedef struct List_Auteur
{
    Sommet_Auteur_TableauxD * tableaux_Somet_hauteur;
    int taille;
}List_Auteur;


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
 * @param [in] OwO 
 */
void printList_Auteur(List_Auteur OwO);


/**
 * @brief Trie Paire_HauteurHeurvre Par noms d'auteur
 * 
 * trie le tableaux Paire_HauteurHeurvre par auteur
 * de facon a avoir toute les oeuvre du meme auteur facilement
 * 
 * auteurA => hoeuvreB 
 * auteurA => hoeuvreA
 * auteurA => hoeuvreU
 * auteurA => hoeuvreT
 * auteurB => hoeuvreB 
 * auteurB => hoeuvreA
 * auteurB => hoeuvreU
 * auteurB => hoeuvreT
 * 
 * @param [in,out]  HauteurHeuvre     Structure a trier
 * @param [in]      sizeHauteurHeuvre taille de la tructure
 */
void sort_tableaux_fiche(Paire_HauteurHeurvre * HauteurHeuvre,int sizeHauteurHeuvre );


// /**
//  * @brief D2PR3CIER génère une liste chainer a partire d'un tableaux
//  * 
//  * 
//  * @param input 
//  * @param list_chainer_auteur 
//  */
// void convertStruct(tableaux_fiche input, ll_list * list_chainer_auteur );
#endif