#include "parsing.h"
#include "list.h"
#include "unwrap.h"
#include <stdio.h>
#include <string.h>


#include "macro.h"



/* Liste Des Fonction TEST a Appeler */

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

//en argument enable des débug ?
void serialized(){
    FILE * in = fopen(originedb,"r");
    exitIfNull(in,"imposible d'ouvrire "originedb);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(serializedb,"w");
    exitIfNull(out,"imposible d'ouvrire "serializedb);
    serialize(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
}
void serializedsmall(){
    FILE * in = fopen(smalloriginedb,"r");
    exitIfNull(in,"imposible d'ouvrire "smalloriginedb);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(smallserializedb,"w");
    exitIfNull(out,"imposible d'ouvrire "smallserializedb);
    serialize(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
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

tab_auteur_struct * unwrap_from_filE(){ //E pas inspi
    FILE * inputDB = fopen(serializedb,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "serializedb)
    return unwrap_from_file(inputDB);
}
void unwrwap_gen_cache(){
    FILE * ouputDB = fopen(serializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "serializedbunwrap)
    tab_auteur_struct * malistauteur = unwrap_from_filE(); //80%
    unwrap_Serilise_Index(malistauteur,ouputDB);           //18%
    unwrap_List_Auteur_free(malistauteur);
}
void unwrwap_gen_cache_small(){
    FILE * ouputDB = fopen(smallserializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "smallserializedbunwrap)
    FILE * inputDB = fopen(smallserializedb,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "smallserializedb)
    tab_auteur_struct * malistauteur = unwrap_from_file(inputDB);
    unwrap_Serilise_Index(malistauteur,ouputDB);
    unwrap_List_Auteur_free(malistauteur);
}
void unwrwap_deserialise(int print){
    FILE * input = fopen(serializedbunwrap,"r");
    exitIfNull(input,"imposible d'ouvrire "serializedbunwrap)
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "serializedb);
    tableaux_fiche * azer = deserialisation(fichier);
    tab_auteur_struct * malistauteur =  unwrap_Deserilise_Index(azer,input);
    if(print == 1){
        printList_Auteur(malistauteur);
    }
    parsing_free(azer);
    unwrap_List_Auteur_free(malistauteur);
}
void ggen_unwrap_Graph(){
    FILE * DBxml = fopen(serializedb,"r");
    FILE * DBinverse = fopen(serializedbunwrap,"r");
    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    gen_unwrap_Graph(DBxml,DBinverse);
}
void uunwrap_ListArticle_from_xml(){
    // plusieuyr pour la taille ?
    FILE * DBxml = fopen(originedb,"r");
    unwrap_ListArticle_from_xml(DBxml);
}

void swap(int print){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tab_auteur_struct * malistedauteur = unwrap_from_file(inputDB);

    if (print==1)
    {
        printList_Auteur(malistedauteur);
    }
}



// soucis de free?
void bench_all(){
    parsing_free(deserialisedb());
    unwrwap_gen_cache();
    unwrwap_deserialise(0);
}

/* Selection de la fonction */

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        //laide qui vien de abench
        printf("PAS BIEN OPTION");
        return 1;
    }

    const char * compstr = argv[1];

    
    //Faire un switch
    if(strcmp("readb",compstr)==0){
        // printf("readb\n");
        readb();    
    }
    else if(strcmp("serialized",compstr)==0){
        // printf("serialized\n");
        serialized();    
    }
    else if(strcmp("serializedsmall",compstr)==0){
        // printf("serialized\n");
        serializedsmall();    
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
    }
    else if (strcmp("unwrwap_gen_cache_small",compstr)==0)
    {
        unwrwap_gen_cache_small();
    }
    else if (strcmp("unwrap_from_file",compstr)==0)
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
    else if (strcmp("gen_unwrap_Graph",compstr)==0)
    {
        ggen_unwrap_Graph();
    }
    else if (strcmp("unwrap_ListArticle_from_xml",compstr)==0)
    {
        uunwrap_ListArticle_from_xml();
    }  
    else{
        fprintf(stderr,"PAS BON TEST!\n");
    }
    return 0;
}
