#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <stdio.h>


//taille de la bar de chargement
#define SIZEBAR 30
//taille balise max pour fgets
#define BALISESIZE 1000

//degrée de verbositée
#define DEBUG_ON
#define INFO_ON
#define WARN_ON
#define PROGRESSBAR_ON
// #define YOLO_ON

#define origineXML               "DATA/dblp.xml"
#define customXML               "DATA/custom.xml"
#define smallorigineXML          "DATA/dblpSmall.xml"
#define Katie           "DATA/test_Katie.xml"
#define cache_fiche             "DATA/SerializedStruc.data"
#define cache_ficheO             "DATA/SerializedStrucKatie.data"
#define small_fiche_cache        "DATA/SerialzedSmall.data"
#define custom_fiche_cache       "DATA/customfichecache.data"
#define auteur_cache       "DATA/SerializedStrucInverse.data"
#define auteur_cacheO       "DATA/SerializedStrucInverseKatie.data"
#define small_auteur_cache  "DATA/SerializedStrucInverseSmall.data"
#define custom_auteur_cache  "DATA/SerializedStrucInverseCustom.data"
#define Article_cache               "DATA/SerializedStrucArticle.data"
#define Article_cacheO               "DATA/SerializedStrucArticleKatie.data"
#define custom_Article_cache      "DATA/SerializedStrucArticleCustom.data"
#define small_Article_cache      "DATA/small_article.data"

//macro pour les couleur
#define GREEN()     fprintf(stderr,"\033[1;32m");
#define BLUE()      fprintf(stderr,"\033[1;34m");
#define RED()       fprintf(stderr,"\033[1;31m");
#define YELLO()     fprintf(stderr,"\033[1;93m");
#define GREY()      fprintf(stderr,"\033[1;90m");
#define CLRCOLOR()  fprintf(stderr,"\033[0m");
#define CLRLINE()   fprintf(stderr,"\033[%dD\033[K",3*SIZEBAR);

//definition des marcro variadique

#ifdef DEBUG_ON
#define DEBUG(...) GREEN() fprintf(stderr,"\033[K\t\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
#else
#define DEBUG(...) ;
#endif
#ifdef INFO_ON
#define INFO(...) BLUE() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
#else
#define INFO(...) ;
#endif
#ifdef WARN_ON
#define WARNING(...) YELLO() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
#else
#define WARNING(...) ;
#endif
#ifdef YOLO_ON
#define YOLO(...) GREY() fprintf(stderr,"\033[K\t\t\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
#else
#define YOLO(...);
#endif
#ifdef PROGRESSBAR_ON
#define PROGRESSBAR(...)            progressbar(__VA_ARGS__);
#define PROGRESSBAR_FILE_PRINT(fichier) progressbar((int)ftell(fichier)>>4&0x0FFFFFFF,nombreligne);
#define PROGRESSBAR_DECL(fichier)       fseek(fichier,0,SEEK_END); int nombreligne = (int)ftell(fichier)>>4&0x0FFFFFFF; fseek(fichier,0,SEEK_SET);
#else
#define PROGRESSBAR(...) ;
#define PROGRESSBAR_FILE_PRINT(...) ;
#define PROGRESSBAR_DECL(...) ;
#define YOLO(...);
#endif

#define ERROR(...) RED() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() ; fprintf(stderr,"\n");

#define exitIfNull(p,...)\
if (!p)\
{\
    ERROR(__VA_ARGS__)\
    exit(1);\
}

#define STR(string) }else if(strcmp(string,compstr)==0){

/**
 * @brief affiche une bar de progression
 * 
 * la taille maximal de la bar est défini par
 * la definition SIZEBAR
 *
 *  
 * @param [in] indice 
 * @param [in] total 
 */
void progressbar(int indice, int total);

/**
 * @brief permet de retirer le \n
 * 
 * @param [in,out] ligne 
 */
void enlever_retour_a_la_ligne(char * ligne);

/**
 * @brief fait x tabbulation pour l'afichage
 * 
 * @param nombre 
 */
void tabulation(int nombre);

/**
 * @brief repete un caracter X foit
 * 
 * pratique pour l'affichage
 * 
 * @param carac 
 * @param nb 
 */
void repchar(char carac,size_t nb);


// typedef struct cache
// {
    
// };


#endif