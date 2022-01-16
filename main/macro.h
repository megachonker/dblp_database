#ifndef MACROH
#define MACROH

#include <stdlib.h>
#include <stdio.h>

#define DEBUG_ON
#define INFO_ON
#define WARN_ON
// #define YOLO_ON

//si fichier tests est benchmark ?

#define customxml               "DATA/custom.xml"
#define originedb               "DATA/dblp.xml"
#define smalloriginedb          "DATA/dblp1sur8.xml"
#define serializedb             "DATA/SerializedStruc.data"
#define smallserializedb        "DATA/Serialzed1000.data"
#define serializedbunwrap       "DATA/SerializedStrucInverse.data"
#define smallserializedbunwrap  "DATA/SerializedStrucInverse1000.data"
#define customserializedbunwrap  "DATA/SerializedStrucInverseCustom.data"
#define serialised_Article      "DATA/SerializedStrucArticle.data"
#define serialised_Articlecustom      "DATA/SerializedStrucArticleCustom.data"

#define SIZEBAR 30

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
#define DEBUG(...) GREEN() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
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
#define YOLO(...) GREY() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");
#else
#define YOLO(...);
#endif

#define ERROR(...) RED() fprintf(stderr,"\033[K\t"); fprintf(stderr, __VA_ARGS__); CLRCOLOR() fprintf(stderr,"\n");

#define exitIfNull(p,...)\
if (!p)\
{\
    ERROR(__VA_ARGS__)\
    exit(1);\
}


void progressbar(int indice, int total);

#endif