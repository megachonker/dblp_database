#include "parsing.h"
#include "list.h"
#include "unwrap.h"
#include <stdio.h>
#include <string.h>


#define originedb           "DATA/dblp.xml"
#define smalloriginedb      "DATA/dblp1sur8.xml"
#define serializedb         "DATA/SerializedStruc.data"
#define smallserializedb    "DATA/Serialzed1000.data"
#define serializedbunwrap   "DATA/SerializedStrucInverse.data"



#define exitIfNull(p,msg)\
if (!p)\
{\
    fprintf(stderr,msg);\
}\



void readb(){
    FILE * fichier = fopen(originedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "originedb);
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void readsmaldb(){
    FILE * fichier = fopen(smalloriginedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "smalloriginedb);
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void serialized(){
    FILE * in = fopen(originedb,"r");
    exitIfNull(in,"imposible d'ouvrire "originedb);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(serializedb,"w");
    exitIfNull(out,"imposible d'ouvrire "serializedb);
    serialize(coucou,out); //utiliser des address pour eviter la copie ?? 
}

//serialise small db manque 

tableaux_fiche * deserialisedb(){
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "serializedb);
    return deserialisation(fichier);    
}

void deserialisesmalldb(){
    FILE * fichier = fopen(smallserializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "smallserializedb);
    deserialisation(fichier);
}

List_Auteur * unwrap_from_filE(){ //E pas inspi
    FILE * inputDB = fopen(serializedb,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "smallserializedb)
    return unwrap_from_file(inputDB);
}
void unwrwap_gen_cache(){
    FILE * ouputDB = fopen(serializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "serializedbunwrap)
    List_Auteur * malistauteur = unwrap_from_filE();
    unwrap_Serilise_Index(malistauteur,ouputDB);
    unwrap_List_Auteur_free(malistauteur);
}
void unwrwap_deserialise(int print){
    FILE * input = fopen(serializedbunwrap,"r");
    exitIfNull(input,"imposible d'ouvrire "serializedbunwrap)
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "serializedb);
    tableaux_fiche * azer = deserialisation(fichier);
    List_Auteur * malistauteur =  unwrap_Deserilise_Index(azer,input);
    if(print == 1){
        printList_Auteur(malistauteur);
    }
    parsing_free(azer);
    unwrap_List_Auteur_free(malistauteur);
}

    // FILE * ouputDB = fopen(serializedbunwrap,"w");
    // exitIfNull(inputDB,"imposible d'ouvrire "serializedbunwrap)

// void testListchainer(){
//     FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
//     exitIfNull(inputDB,"INPUT PAS CHEMAIN")
//     ll_list * Liste_chainer = deserialisation_Liste(inputDB);
//     ll_list_link(Liste_chainer);
//     print_liste_chainer_Auteur_titre(Liste_chainer);
//     tableaux_fiche mesfiches = deserialisation(inputDB);

//     ll_list * Liste_chainer = ll_create();
//     Sommet_Auteur_ListChainer new_sommet;
//     new_sommet.auteur = mesfiches.fiche[0]->liste_auteur[0];
//     new_sommet.titre_article = ll_create();
//     ll_append(new_sommet.titre_article,mesfiches.fiche[0]->titre);
//     ll_append(Liste_chainer,&new_sommet);

//     convertStruct(mesfiches,Liste_chainer);

//     print_liste_chainer_Auteur_titre(Liste_chainer);
// }

void swap(int print){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    List_Auteur * malistedauteur = unwrap_from_file(inputDB);

    if (print==1)
    {
        printList_Auteur(malistedauteur);
    }
}

void bench_all(){
    parsing_free(deserialisedb());
    unwrwap_gen_cache();
    unwrwap_deserialise(0);
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
    else if(strcmp("serialized",compstr)==0){
        // printf("serialized\n");
        serialized();    
    }
    else if(strcmp("deserialisedb",compstr)==0){// N
        // printf("deserialisedb\n");
        deserialisedb();    
    }
    else if(strcmp("deserialisedbprint",compstr)==0){// N
        // printf("deserialisedb\n");
        printTabmeaux(*deserialisedb());
    }
    else if(strcmp("readsmaldb",compstr)==0){
        // printf("readsmaldb\n");
        readsmaldb();
    }
    else if(strcmp("deserialisesmalldb",compstr)==0){
        // printf("deserialisesmalldb:\n");
        deserialisesmalldb();
    }
    else if (strcmp("ALL",compstr)==0){
        bench_all();
    }
    else if (strcmp("swap",compstr)==0){
        swap(0);
    }
    else if(strcmp("swaprint",compstr)==0){
        swap(1);
    }else if (strcmp("unwrwap_gen_cache",compstr)==0)
    {
        unwrwap_gen_cache();
    }else if (strcmp("unwrap_from_file",compstr)==0)
    {
        unwrap_from_filE();
    }
    else if (strcmp("unwrwap_deserialise",compstr)==0)
    {
        unwrwap_deserialise(0);
    }
    else if (strcmp("unwrwap_deserialiseprint",compstr)==0)
    {
        unwrwap_deserialise(1);
    }
    else{
        fprintf(stderr,"PAS BON TEST!\n");
    }
    return 0;
}
