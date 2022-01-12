#include <stdlib.h>

#define DEBUG_ON
#define INFO_ON
#define WARN_ON

//si fichier tests est benchmark ?

#define originedb           "DATA/dblp.xml"
#define smalloriginedb      "DATA/dblp1sur8.xml"
#define serializedb         "DATA/SerializedStruc.data"
#define smallserializedb    "DATA/Serialzed1000.data"
#define serializedbunwrap   "DATA/SerializedStrucInverse.data"
#define smallserializedbunwrap    "DATA/SerializedStrucInverse1000.data"
#define customxml    "DATA/custom.xml"

//macro pour les couleur
#define GREEN() fprintf(stderr,"\033[1;32m");
#define BLUE()  fprintf(stderr,"\033[1;34m");
#define RED()   fprintf(stderr,"\033[1;31m"); //faire un fprint
#define CLR()   fprintf(stderr,"\033[0m");

//definition des marcro variadique

#ifdef DEBUG_ON
#define DEBUG(...) GREEN() fprintf(stderr, __VA_ARGS__); CLR() fprintf(stderr,"\n");
#else
#define DEBUG(TEST) ;
#endif

#ifdef INFO_ON
#define INFO(...) BLUE() fprintf(stderr, __VA_ARGS__); CLR() fprintf(stderr,"\n");
#else
#define INFO(TEST) ;
#endif
// #ifdef WARN_ON
// WARNING() INFO DEBUG       PROGRESS BAR?                          YELLO
// #endif

#define ERROR(...) RED() fprintf(stderr, __VA_ARGS__); CLR() fprintf(stderr,"\n");//faire un fprint

#define exitIfNull(p,...)\
if (!p)\
{\
    ERROR(__VA_ARGS__)\
    exit(1);\
}
