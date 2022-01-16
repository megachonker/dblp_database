#include "parsing.h"
#include "unwrap.h"
#include <stdio.h>
#include <string.h>


#include "macro.h"

//fair des argument preselectioner pour toute les fonction 1 defaut dblp 2 dblp1000 3 custom

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
    serialisation_tableaux_fiche(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
}
void serializedsmall(){
    FILE * in = fopen(smalloriginedb,"r");
    exitIfNull(in,"imposible d'ouvrire "smalloriginedb);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(smallserializedb,"w");
    exitIfNull(out,"imposible d'ouvrire "smallserializedb);
    serialisation_tableaux_fiche(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
}
//serialise small db manque 

tableaux_fiche * deserialisedb(){
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "serializedb);
    return deserialisation_tableaux_fiche(fichier);    
}

void deserialisesmalldb(){
    FILE * fichier = fopen(smallserializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "smallserializedb);
    deserialisation_tableaux_fiche(fichier);
}

tab_auteur_struct * unwrap_from_filE(){ //E pas inspi
    FILE * inputDB = fopen(serializedb,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "serializedb)
    return tab_auteur_from_file(inputDB);
}
void unwrwap_gen_cache(){
    FILE * ouputDB = fopen(serializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "serializedbunwrap)
    tab_auteur_struct * malistauteur = unwrap_from_filE(); //80%
    serialise_tab_auteur_struct(malistauteur,ouputDB);           //18%
    unwrap_List_Auteur_free(malistauteur);
}
void unwrwap_gen_cache_small(){
    FILE * ouputDB = fopen(smallserializedbunwrap,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "smallserializedbunwrap)
    FILE * inputDB = fopen(smallserializedb,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "smallserializedb)
    tab_auteur_struct * malistauteur = tab_auteur_from_file(inputDB);
    serialise_tab_auteur_struct(malistauteur,ouputDB);
    unwrap_List_Auteur_free(malistauteur);
}
tab_auteur_struct * deserialise_tab_auteur(int print){
    FILE * input = fopen(serializedbunwrap,"r");
    exitIfNull(input,"imposible d'ouvrire "serializedbunwrap)
    FILE * fichier = fopen(serializedb,"r");
    exitIfNull(fichier,"imposible d'ouvrire "serializedb);
    tableaux_fiche * azer = deserialisation_tableaux_fiche(fichier);
    tab_auteur_struct * malistauteur =  deserialise_tab_auteur_struct(azer,input);
    if(print == 1){
        printList_auteur(malistauteur);
    }
    return malistauteur;
}
void ggen_unwrap_Graph(){
    FILE * DBxml = fopen(serializedb,"r");
    FILE * DBinverse = fopen(serializedbunwrap,"r");
    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    gen_unwrap_Graph(DBxml,DBinverse);
}
void uunwrap_ListArticle_from_xml(int a){
    // plusieuyr pour la taille ?
    FILE * DBxml = fopen(originedb,"r");   
    tab_Article_struct * montab = gen_tab_Article_from_xml(DBxml);
    if (a)
    {
        printList_Article(montab);
    }
}
tab_Article_struct * gen_article(){
    FILE * DBxmll = fopen(serializedb,"r");
    FILE * DBinversee = fopen(serializedbunwrap,"r");
    exitIfNull(DBxmll,"INPUT PAS CHEMAIN")
    exitIfNull(DBinversee,"INPUT PAS CHEMAIN")
    tableaux_fiche * matablefiche = deserialisation_tableaux_fiche(DBxmll);
    tab_auteur_struct * malistaauteur =   deserialise_tab_auteur_struct(matablefiche,DBinversee);
    tab_Article_struct * malistearticle = convertTab_Article2auteur(malistaauteur);
    return malistearticle;
}

void serialisation_tab_Article_structt(){
    FILE * DBarticle = fopen(serialised_Article,"w");
    exitIfNull(DBarticle,"INPUT PAS CHEMAIN");
    serialisation_tab_Article_struct(gen_article(),DBarticle);
}

void deserialisation_tab_Article_structt(){
    FILE * DBxml = fopen(serializedb,"r");
    FILE * DBinverse = fopen(serialised_Article,"r");
    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    tab_auteur_struct * matablefiche = deserialise_tab_auteur(0);
    deserialisation_tab_Article_struct(matablefiche,DBinverse);
}

void swap(int print){
    FILE * inputDB = fopen("DATA/SerializedStruc.data","r");
    exitIfNull(inputDB,"INPUT PAS CHEMAIN")
    tab_auteur_struct * malistedauteur = tab_auteur_from_file(inputDB);

    if (print==1)
    {
        printList_auteur(malistedauteur);
    }
}



// soucis de free?
void bench_all(){
    parsing_free(deserialisedb());
    unwrwap_gen_cache();
    deserialise_tab_auteur(0);
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
    else if (strcmp("tab_auteur_from_file",compstr)==0)
    {
        unwrap_from_filE();
    }
    else if (strcmp("deserialise_tab_auteur",compstr)==0)
    {
        deserialise_tab_auteur(0);
    }
    else if (strcmp("deserialise_tab_auteurprint",compstr)==0)
    {
        deserialise_tab_auteur(1);
    }
    else if (strcmp("gen_unwrap_Graph",compstr)==0)
    {
        ggen_unwrap_Graph();
    }
    else if (strcmp("gen_tab_Article_from_xml",compstr)==0)
    {
        uunwrap_ListArticle_from_xml(0);
    }
    else if (strcmp("unwrap_ListArticle_from_xmlprint",compstr)==0)
    {
        uunwrap_ListArticle_from_xml(1);
    }else if (strcmp("unwrap_deserialise_Article",compstr)==0)
    {
        deserialisation_tab_Article_structt();
    }
    else if (strcmp("unwrap_serialise_Article",compstr)==0)
    {
        serialisation_tab_Article_structt();
    }
    // else if (strcmp("unwrap_serialise_Article",compstr)==0)
    // {
    //     serialisation_tab_Article_structt();
    // }
    else if (strcmp("gen_article",compstr)==0)
    {
        gen_article();
    }
    // else if (strcmp("deserialisation_tab_auteur_struct",compstr)==0)
    // {
    //     deserialisation_tab_auteur_structt();
    // }
    else{
        fprintf(stderr,"PAS BON TEST!\n");
    }
    CLRLINE()
    return 0;
}
