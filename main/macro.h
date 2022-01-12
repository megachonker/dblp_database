

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
#define GREEN() printf("\033[1;32m");
#define BLUE()  printf("\033[1;34m");
#define RED()   printf("\033[1;31m"); //faire un fprint
#define CLR()   printf("\033[0m");

//definition des marcro variadique

#ifdef DEBUG_ON
#define DEBUG(...) GREEN() printf (__VA_ARGS__); CLR() printf("\n");
#else
#define DEBUG(TEST) ;
#endif

#ifdef INFO_ON
#define INFO(...) BLUE() printf (__VA_ARGS__); CLR() printf("\n");
#else
#define INFO(TEST) ;
#endif
// #ifdef WARN_ON
// WARNING() INFO DEBUG                                 YELLO
// #endif

#define ERROR(...) RED() printf (__VA_ARGS__); CLR() printf("\n");//faire un fprint

//a Pimper la fonction

#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\



// exitiffnull si 0 ou NULL un vrais exit un print des message avec error