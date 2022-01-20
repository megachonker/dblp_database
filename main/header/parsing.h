#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>

/**
 * @brief Entrée DBLP Titre et liste des auteur 
 * 
 * au long terme devra contenire tout les champs
 * structure étant alouer dynamiquement pour pouvoir être utiliser par plusieur autre structure
 * 
 */
typedef struct fiche_minimale
{
    char * titre;           ///< renomer par article ?
    //< date de création ?
    int nombre_auteur;      ///< nombre d'auteur contenue dans liste_auteur
    char ** liste_auteur;   ///< liste de liste de caractere des noms d'auteur (Trier gain perf ?)
    int ADDR;               ///< Indice permetant d'acceder a cette fiche_minimale depuis tableaux_fiche.fiche[ADDR] (initialiser a la création) 
}fiche_minimale;



/**
 * @brief Contien toute les fiche_minimale
 * 
 * Chaque addresse fiche_minimale est contenu dans un tableaux dynamique
 * nbAuteurXarticle est utiliser pour retrouver l'index quand on désérialise
 * 
 * @struct tableaux_fiche
 */
typedef struct tableaux_fiche
{
    fiche_minimale * fiche; ///< tableaux d'adresse pointant ver des adrese dynamique contenant fiche_minimale 
    int taille;             ///<taille tableaux
    int nbAuteurXarticle;   //< index reflétant l'ordre de création
}tableaux_fiche;


/**
 * @brief Parse un fichier XML DBLP
 * 
 *  Va générée un tableaux_fiche ainsie que ces fiche_minimale
 * -    Article
 * -    auteur
 *  
 *  mais aussi
 *  - génère ADDR de chaque fiche
 *  - trie les fiche
 *  
 * ## Doit pouvoir utiliser les date !
 * 
 * @param inputDB 
 * @return tableaux_fiche 
 */
tableaux_fiche parse(FILE * inputDB);


//arename
/**
 * @brief Print tableaux_fiche
 * 
 * print tout les élément de tableaux_fiche en fesant appelle a printM
 * 
 * @param [in] OwU 
 */
void printTabmeaux(tableaux_fiche OwU);

/**
 * @brief Sérialisation du XML
 * 
 *  ajouter un truc pour la validitée checksum du programe qui la compiler ?
 * 
 * @param [in] mastertab structure tableaux_fiche a sérialiser
 * @param [out] output    fichier de sortie 
 */
void serialisation_tableaux_fiche(tableaux_fiche mastertab, FILE * outfichier);

/**
 * @brief génère tableaux_fiche depuis un cache générée par serialisation_tableaux_fiche 
 * 
 * test avec des maloc 
 * 
 * @param [in] input générée par serialisation_tableaux_fiche 
 * @return pointeur ver tableaux_fiche 
 */
tableaux_fiche deserialisation_tableaux_fiche(FILE * input);

//renomer
/**
 * @brief free tableaux_fiche
 * 
 * @param DEGAGE 
 */
void free_tab_fiche(tableaux_fiche DEGAGE);
void free_fiche_minimale(fiche_minimale fiche);
#endif