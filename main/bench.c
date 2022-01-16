#include "parsing.h"
#include "unwrap.h"
#include <stdio.h>
#include <string.h>


#include "macro.h"

enum{
    dblp,
    smalldblp,
    customdb,
    Katie des argument preselectioner pour toute les fonction 1 defaut dblp 2 dblp1000 3 custom

/* Liste Des Fonction TEST a Appeler */

void readb(){
    FILE * fichier = fopen(origineXML,"r");
    exitIfNull(fichier,"imposible d'ouvrire "origineXML);
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

void readsmaldb(){
    FILE * fichier = fopen(smallorigineXML,"r");
    exitIfNull(fichier,"imposible d'ouvrire "smallorigineXML);
    parse(fichier); //utiliser des address pour eviter la copie ?? 
}

//en argument enable des débug ?
void serialized(){
    FILE * in = fopen(origineXML,"r");
    exitIfNull(in,"imposible d'ouvrire "origineXML);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(cache_fiche,"w");
    exitIfNull(out,"imposible d'ouvrire "cache_fiche);
    serialisation_tableaux_fiche(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
}
void serializedsmall(){
    FILE * in = fopen(smallorigineXML,"r");
    exitIfNull(in,"imposible d'ouvrire "smallorigineXML);
    tableaux_fiche coucou = parse(in); //utiliser des address pour eviter la copie ?? 
    FILE * out = fopen(small_fiche_cache,"w");
    exitIfNull(out,"imposible d'ouvrire "small_fiche_cache);
    serialisation_tableaux_fiche(coucou,out); //utiliser des address pour eviter la copie ??
    // printTabmeaux(coucou);
}
//serialise small db manque 

tableaux_fiche * deserialisedb(){
    FILE * fichier = fopen(cache_fiche,"r");
    exitIfNull(fichier,"imposible d'ouvrire "cache_fiche);
    return deserialisation_tableaux_fiche(fichier);    
}

void deserialisesmalldb(){
    FILE * fichier = fopen(small_fiche_cache,"r");
    exitIfNull(fichier,"imposible d'ouvrire "small_fiche_cache);
    deserialisation_tableaux_fiche(fichier);
}

tab_auteur_struct * unwrap_from_filE(){ //E pas inspi
    FILE * inputDB = fopen(cache_fiche,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "cache_fiche)
    return tab_auteur_from_file(inputDB);
}
void unwrwap_gen_cache(){
    FILE * ouputDB = fopen(auteur_cache,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "auteur_cache)
    tab_auteur_struct * malistauteur = unwrap_from_filE(); //80%
    serialise_tab_auteur_struct(malistauteur,ouputDB);           //18%
    unwrap_List_Auteur_free(malistauteur);
}
void unwrwap_gen_cache_small(){
    FILE * ouputDB = fopen(small_auteur_cache,"w");
    exitIfNull(ouputDB,"imposible d'ouvrire "small_auteur_cache)
    FILE * inputDB = fopen(small_fiche_cache,"r");
    exitIfNull(inputDB,"imposible d'ouvrire "small_fiche_cache)
    tab_auteur_struct * malistauteur = tab_auteur_from_file(inputDB);
    serialise_tab_auteur_struct(malistauteur,ouputDB);
    unwrap_List_Auteur_free(malistauteur);
}
tab_auteur_struct * deserialise_tab_auteur(int print){
    FILE * input = fopen(auteur_cache,"r");
    exitIfNull(input,"imposible d'ouvrire "auteur_cache)
    FILE * fichier = fopen(cache_fiche,"r");
    exitIfNull(fichier,"imposible d'ouvrire "cache_fiche);
    tableaux_fiche * azer = deserialisation_tableaux_fiche(fichier);
    tab_auteur_struct * malistauteur =  deserialise_tab_auteur_struct(azer,input);
    if(print == 1){
        printList_auteur(malistauteur);
    }
    return malistauteur;
}
void ggen_unwrap_Graph(){
    FILE * DBxml = fopen(cache_fiche,"r");
    FILE * DBinverse = fopen(auteur_cache,"r");
    FILE * DBarticle = fopen(Article_cache,"r");
    exitIfNull(DBxml,"INPUT PAS CHEMAIN")
    exitIfNull(DBinverse,"INPUT PAS CHEMAIN")
    exitIfNull(DBarticle,"INPUT PAS CHEMAIN")
    deserialise_Graph(DBxml,DBinverse,DBarticle);
}
void uunwrap_ListArticle_from_xml(int a){
    // plusieuyr pour la taille ?
    FILE * DBxml = fopen(origineXML,"r");   
    tab_Article_struct * montab = gen_tab_Article_from_xml(DBxml);
    if (a)
    {
        printList_Article(montab);
    }
}
tab_Article_struct * gen_article(){
    FILE * DBxmll = fopen(cache_fiche,"r");
    FILE * DBinversee = fopen(auteur_cache,"r");
    exitIfNull(DBxmll,"INPUT PAS CHEMAIN")
    exitIfNull(DBinversee,"INPUT PAS CHEMAIN")
    tableaux_fiche * matablefiche = deserialisation_tableaux_fiche(DBxmll);
    tab_auteur_struct * malistaauteur =   deserialise_tab_auteur_struct(matablefiche,DBinversee);
    tab_Article_struct * malistearticle = convertTab_auteur2Article(malistaauteur);
    return malistearticle;
}

void serialisation_tab_Article_structt(){
    FILE * DBarticle = fopen(Article_cache,"w");
    exitIfNull(DBarticle,"INPUT PAS CHEMAIN");
    serialisation_tab_Article_struct(gen_article(),DBarticle);
}

void deserialisation_tab_Article_structt(){
    FILE * DBxml = fopen(cache_fiche,"r");
    FILE * DBinverse = fopen(Article_cache,"r");
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


void local_deserialise_Graph(){
    FILE * DBficheLecture   = fopen(cache_fiche     ,"r");
    FILE * DBauteurLecture  = fopen(auteur_cache    ,"r");
    FILE * DBArticleLecture = fopen(Article_cache   ,"r");


    deserialise_Graph(DBficheLecture
                                    ,DBauteurLecture
                                    ,DBArticleLecture);

    exitIfNull(DBficheLecture  ,"erreur ouverture bd")
    exitIfNull(DBauteurLecture ,"erreur ouverture bd")
    exitIfNull(DBArticleLecture,"erreur ouverture bd")

    fclose(DBficheLecture);
    fclose(DBauteurLecture);
    fclose(DBArticleLecture);
}

unwrap_Graph_struct local_gen_Graph_from_XML(){
    FILE * XML               = fopen(origineXML      ,"r");
    exitIfNull(XML  ,"erreur ouverture bd")
    return gen_Graph_from_XML(XML);
    fclose(XML);
}

void local_serialise_Graph(){

    unwrap_Graph_struct graph = local_gen_Graph_from_XML();

    FILE * DBficheEcriture   = fopen(cache_fiche     ,"w");
    FILE * DBauteurEcriture  = fopen(auteur_cache    ,"w");
    FILE * DBArticleEcriture = fopen(Article_cache   ,"w");

    serialise_Graph(graph   ,DBficheEcriture
                            ,DBauteurEcriture
                            ,DBArticleEcriture);

    fclose(DBficheEcriture);
    fclose(DBauteurEcriture);
    fclose(DBArticleEcriture);

}

unwrap_Graph_struct local_gen_custom_Graph_from_XML(){
    FILE * XML               = fopen(customXML      ,"r");
    exitIfNull(XML  ,"erreur ouverture bd")
    return gen_Graph_from_XML(XML);
    fclose(XML);
}


void local_custom_serialise_Graph(){

    unwrap_Graph_struct graph = local_gen_Graph_from_XML();

    FILE * DBficheEcriture   = fopen(custom_fiche_cache     ,"w");
    FILE * DBauteurEcriture  = fopen(custom_auteur_cache    ,"w");
    FILE * DBArticleEcriture = fopen(custom_Article_cache   ,"w");

    serialise_Graph(graph   ,DBficheEcriture
                            ,DBauteurEcriture
                            ,DBArticleEcriture);

    fclose(DBficheEcriture);
    fclose(DBauteurEcriture);
    fclose(DBArticleEcriture);

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
    const char * compstr = argv[1];

    if (argc == 3)
    {
        FILE * XML                  = NULL ;
        FILE * DBficheLecture       = NULL ;
        FILE * DBauteurLecture      = NULL ;
        FILE * DBArticleLecture     = NULL ;
        FILE * DBficheEcriture      = NULL ;
        FILE * DBauteurEcriture     = NULL ;
        FILE * DBArticleEcriture    = NULL ;


        switch (atoi(argv[2]))
        {
        case dblp:
            XML               = fopen(origineXML      ,"r");
            DBficheLecture    = fopen(cache_fiche     ,"r");
            DBauteurLecture   = fopen(auteur_cache    ,"r");
            DBArticleLecture  = fopen(Article_cache   ,"r");
            // DBficheEcriture   = fopen(cache_fiche     ,"w");
            // DBauteurEcriture  = fopen(auteur_cache    ,"w");
            // DBArticleEcriture = fopen(Article_cache   ,"w");
            break;
        case smalldblp:
            XML               = fopen(smallorigineXML     ,"r");
            DBficheLecture    = fopen(small_fiche_cache  ,"r");
            DBauteurLecture   = fopen(small_auteur_cache ,"r");
            DBArticleLecture  = fopen(small_Article_cache,"r");
            DBficheEcriture   = fopen(small_fiche_cache  ,"w");
            DBauteurEcriture  = fopen(small_auteur_cache ,"w");
            DBArticleEcriture = fopen(small_Article_cache,"w");
            break;
        case customdb:
            XML               = fopen(customXML              ,"r");
            DBficheLecture    = fopen(custom_fiche_cache     ,"r");
            DBauteurLecture   = fopen(custom_auteur_cache    ,"r");
            DBArticleLecture  = fopen(custom_Article_cache   ,"r");
            DBficheEcriture   = fopen(custom_fiche_cache     ,"w");
            DBauteurEcriture  = fopen(custom_auteur_cache    ,"w");
            DBArticleEcriture = fopen(custom_Article_cache   ,"w");
            break;
        case Katie:
            XML               = fopen(Katie      ,"r");
            DBficheLecture    = fopen(cache_fiche     ,"r");
            DBauteurLecture   = fopen(auteur_cache    ,"r");
            DBArticleLecture  = fopen(Article_cache   ,"r");
            DBficheEcriture   = fopen(cache_fiche     ,"w");
            DBauteurEcriture  = fopen(auteur_cache    ,"w");
            DBArticleEcriture = fopen(Article_cache   ,"w");
            break;   
        default:
            break;
        }
        exitIfNull(XML              ,"erreur ouverture bd %s.",origineXML)


        exitIfNull(DBficheEcriture  ,"erreur ouverture bd %s.",cache_fiche)
        exitIfNull(DBauteurEcriture ,"erreur ouverture bd %s.",auteur_cache)
        exitIfNull(DBArticleEcriture,"erreur ouverture bd %s.",Article_cache)

        //Faire un switch
        if(strcmp("serialize_graph",compstr)==0){
            serialise_Graph(gen_Graph_from_XML(XML),
                DBficheEcriture,
                DBauteurEcriture,
                DBArticleEcriture);
        }

        exitIfNull(DBficheLecture   ,"erreur ouverture bd %s.",cache_fiche)
        exitIfNull(DBauteurLecture  ,"erreur ouverture bd %s.",auteur_cache)
        exitIfNull(DBArticleLecture ,"erreur ouverture bd %s.",Article_cache)

        //Faire un switch
        if(strcmp("deserialize_graph",compstr)==0){
            deserialise_Graph(
                DBficheEcriture,
                DBauteurEcriture,
                DBArticleEcriture);
        }

        CLRLINE()

        // fclose(DBficheEcriture);
        // fclose(DBauteurEcriture);
        // fclose(DBArticleEcriture);
        // fclose(DBficheEcriture);
        // fclose(DBauteurEcriture);
        // fclose(DBArticleEcriture);

        return 0;
    }else if (argc != 2)
    {
        //laide qui vien de abench
        printf("PAS BIEN OPTION");
        return 1;
    }


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
    else if (strcmp("deserialise_Graph",compstr)==0)
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
    else if (strcmp("deserialise_Graph",compstr)==0)
    {
        local_deserialise_Graph();
    }
    else if (strcmp("gen_graph_from_XML",compstr)==0)
    {
        local_gen_Graph_from_XML();
    }
    else if (strcmp("serialise_Graph",compstr)==0)
    {
        local_serialise_Graph();
    }
    
    // else if (strcmp("deserialisation_tab_auteur_struct",compstr)==0)
    // {
    //     deserialisation_tab_auteur_structt();
    // }
    else{
        fprintf(stderr,"PAS BON TEST!\n");
        fprintf(stderr,"\
    \n- readb\
    \n- readsmaldb\
    \n- serialized\
    \n- serializedsmall\
    \n- deserialisedb\
    \n- deserialisesmalldb\
    \n- swap\
    \n- swaprint\
    \n- unwrwap_gen_cache\
    \n- tab_auteur_from_file\
    \n- deserialise_tab_auteur\
    \n- unwrwap_gen_cache_small\
    \n- deserialise_Graph\
    \n- gen_tab_Article_from_xml\
    \n- unwrap_deserialise_Article\
    \n- gen_graph_from_XML\
    \n- serialise_Graph\
    \n- ALL");
    }
    CLRLINE()
    return 0;
}
