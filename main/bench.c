#include "parsing.h"
#include <stdio.h>
#include <string.h>


#define originedb           "DATA/dblp.xml"
#define smalloriginedb      "DATA/dblp1sur8.xml"
#define serializedb         "DATA/SerializedStruc.data"
#define smallserializedb    "DATA/Serialzed1000.data"



#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\



void readb(){
    FILE * fichier = fopen(originedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire");
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void readsmaldb(){
    FILE * fichier = fopen(smalloriginedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire");
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void readbCOPY(){
    FILE * fichier = fopen(originedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire");
    tableaux_fiche coucou = parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void serialized(){
    FILE * in = fopen(originedb,"r");
    exitIfNull(in,"imposible d'ouvrire");
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(serializedb,"w");
    exitIfNull(out,"imposible d'ouvrire");
    serialize(coucou,out); //utiliser des address pour eviter la copie ?? 
}

void deserialisedb(){
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire");
    deserialisation(fichier);    
}

void deserialisesmalldb(){
    FILE * fichier = fopen(smallserializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire deserialisesmalldb");
    deserialisation(fichier);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("PAS BIEN OPTION");
        return 1;
    }

    const char * compstr = argv[1];


    if(strcmp("readb",compstr)==0){
        // printf("readb\n");
        readb();    
    }
    else if(strcmp("readbCOPY",compstr)==0){
        // printf("readbCOPY\n");
        readbCOPY();    
    }
    else if(strcmp("serialized",compstr)==0){
        // printf("serialized\n");
        serialized();    
    }
    else if(strcmp("deserialisedb",compstr)==0){// N
        // printf("deserialisedb\n");
        deserialisedb();    
    }
    else if(strcmp("readsmaldb",compstr)==0){
        // printf("readsmaldb\n");
        readsmaldb();
    }
    else if(strcmp("deserialisesmalldb",compstr)==0){
        // printf("deserialisesmalldb:\n");
        deserialisesmalldb();
    }else{
        fprintf(stderr,"PAS BON TEST!\n");
    }
    return 0;
}
